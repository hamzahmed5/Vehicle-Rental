#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
using namespace std;

// ====== Data Structures ======
struct Date {
    int day, month, year;
    Date(int d = 1, int m = 1, int y = 2025) : day(d), month(m), year(y) {}
    string toString() const {
        return to_string(day) + "/" + to_string(month) + "/" + to_string(year);
    }
};

struct Vehicle {
    string name, manufacturer;
    int model, year, id;
    float price, rentPricePerDay;
    Date manufactureDate;
    bool isAvailableForRent, isAvailableForSale;

    Vehicle(string n = "Unknown", int m = 0, float p = 0, int i = 0, float r = 0, string manu = "Unknown", int y = 2025, bool rent = true, bool sale = true, Date d = Date())
        : name(n), manufacturer(manu), model(m), year(y), price(p), rentPricePerDay(r), id(i), manufactureDate(d), isAvailableForRent(rent), isAvailableForSale(sale) {}

    void display() const {
        cout << left << setw(25) << name << setw(10) << model << setw(10) << fixed << setprecision(2) << price << setw(10) << id;
        cout << setw(15) << (isAvailableForRent ? to_string(rentPricePerDay) : "N/A")
             << setw(10) << (isAvailableForSale ? "Yes" : "No")
             << setw(10) << (isAvailableForRent ? "Yes" : "No") << endl;
    }
};

struct Customer {
    string fullName, address, email;
    int phone;
    Customer(string name = "", int ph = 0, string addr = "", string em = "") : fullName(name), phone(ph), address(addr), email(em) {}

    void input() {
        cout << "Enter full name: "; cin.ignore(); getline(cin, fullName);
        cout << "Enter phone number: "; cin >> phone; cin.ignore();
        cout << "Enter address: "; getline(cin, address);
        cout << "Enter email: "; getline(cin, email);
    }
    void displayInfo() const {
        cout << "Customer: " << fullName << endl << "Phone: " << phone << endl << "Address: " << address << endl << "Email: " << email << endl;
    }
};

struct Transaction {
    static int transactionCount;
    int transactionId;
    Customer customer;
    Vehicle vehicle;
    Date startDate, endDate;
    float totalAmount;
    bool isActive;
    char type; // 'R' for rental, 'S' for sale

    Transaction(const Customer& cust = Customer(), const Vehicle& veh = Vehicle(), const Date& start = Date(), const Date& end = Date(), char t = 'R')
        : customer(cust), vehicle(veh), startDate(start), endDate(end), isActive(true), type(t) {
        transactionId = ++transactionCount;
        totalAmount = (type == 'R') ? calculateDays(start, end) * vehicle.rentPricePerDay : vehicle.price;
    }
    int calculateDays(const Date& start, const Date& end) const {
        int days = (end.year - start.year) * 365 + (end.month - start.month) * 30 + (end.day - start.day) + 1;
        return days;
    }
    void displayReceipt() const {
        if (type == 'R') {
            cout << "\n------ RENTAL RECEIPT #" << transactionId << " ------\n";
            customer.displayInfo();
            cout << "Car: " << vehicle.name << endl;
            cout << "Start Date: " << startDate.toString() << endl;
            cout << "End Date: " << endDate.toString() << endl;
            cout << "Rental Price Per Day: $" << fixed << setprecision(2) << vehicle.rentPricePerDay << endl;
            cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
            cout << "Status: " << (isActive ? "Active" : "Completed") << endl;
        } else {
            cout << "\n------ SALE INVOICE #" << transactionId << " ------\n";
            customer.displayInfo();
            cout << "Car: " << vehicle.name << endl;
            cout << "Price: $" << fixed << setprecision(2) << vehicle.price << endl;
            cout << "Manufacture Date: " << vehicle.manufactureDate.toString() << endl;
            cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        }
        cout << "-------------------------------\n";
    }
};
int Transaction::transactionCount = 0;

// ====== Linked List for Vehicles ======
struct VehicleNode {
    Vehicle data;
    VehicleNode* next;
    VehicleNode(const Vehicle& v) : data(v), next(nullptr) {}
};

class VehicleLinkedList {
    VehicleNode* head;
    int size;
public:
    VehicleLinkedList() : head(nullptr), size(0) {}
    ~VehicleLinkedList() { clear(); }
    void insert(const Vehicle& vehicle) {
        VehicleNode* newNode = new VehicleNode(vehicle);
        if (!head) head = newNode;
        else {
            VehicleNode* curr = head;
            while (curr->next) curr = curr->next;
            curr->next = newNode;
        }
        size++;
    }
    bool remove(int id) {
        if (!head) return false;
        if (head->data.id == id) {
            VehicleNode* temp = head; head = head->next; delete temp; size--; return true;
        }
        VehicleNode* curr = head;
        while (curr->next && curr->next->data.id != id) curr = curr->next;
        if (curr->next) {
            VehicleNode* temp = curr->next;
            curr->next = curr->next->next; delete temp; size--; return true;
        }
        return false;
    }
    Vehicle* search(int id) {
        VehicleNode* curr = head;
        while (curr) { if (curr->data.id == id) return &curr->data; curr = curr->next; }
        return nullptr;
    }
    void displayAll() const {
        for (VehicleNode* curr = head; curr; curr = curr->next) curr->data.display();
    }
    void displayFiltered(bool forSale, bool forRent) const {
        for (VehicleNode* curr = head; curr; curr = curr->next)
            if ((forSale && curr->data.isAvailableForSale) || (forRent && curr->data.isAvailableForRent))
                curr->data.display();
    }
    bool updateAvailability(int id, bool forSale, bool forRent) {
        Vehicle* v = search(id);
        if (v) { v->isAvailableForSale = forSale; v->isAvailableForRent = forRent; return true; }
        return false;
    }
    void clear() { while (head) { VehicleNode* temp = head; head = head->next; delete temp; } size = 0; }
    int getSize() const { return size; }
    Vehicle* toArray() const {
        if (size == 0) return nullptr;
        Vehicle* arr = new Vehicle[size];
        VehicleNode* curr = head; int idx = 0;
        while (curr) { arr[idx++] = curr->data; curr = curr->next; }
        return arr;
    }
};

// ====== Stack for Transactions ======
template<typename T>
class Stack {
    struct Node { T data; Node* next; Node(const T& d) : data(d), next(nullptr) {} };
    Node* top; int size;
public:
    Stack() : top(nullptr), size(0) {}
    ~Stack() { clear(); }
    void push(const T& item) { Node* n = new Node(item); n->next = top; top = n; size++; }
    bool pop() { if (!top) return false; Node* t = top; top = top->next; delete t; size--; return true; }
    T peek() const { if (!top) throw runtime_error("Stack is empty"); return top->data; }
    bool isEmpty() const { return !top; }
    int getSize() const { return size; }
    void clear() { while (top) pop(); }
    void display() const { for (Node* n = top; n; n = n->next) cout << "Transaction ID: " << n->data.transactionId << endl; }
};

// ====== Queue for Customers ======
template<typename T>
class Queue {
    struct Node { T data; Node* next; Node(const T& d) : data(d), next(nullptr) {} };
    Node* front, *rear; int size;
public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}
    ~Queue() { clear(); }
    void enqueue(const T& item) {
        Node* n = new Node(item);
        if (!front) front = rear = n; else { rear->next = n; rear = n; }
        size++;
    }
    bool dequeue() {
        if (!front) return false;
        Node* t = front; front = front->next; if (!front) rear = nullptr; delete t; size--; return true;
    }
    T getFront() const { if (!front) throw runtime_error("Queue is empty"); return front->data; }
    bool isEmpty() const { return !front; }
    int getSize() const { return size; }
    void clear() { while (front) dequeue(); }
    void display() const { for (Node* n = front; n; n = n->next) cout << "Customer: " << n->data.fullName << endl; }
};

// ====== Searching & Sorting Algorithms ======
class SearchSort {
public:
    static int linearSearch(Vehicle* arr, int size, int targetId) {
        for (int i = 0; i < size; i++) if (arr[i].id == targetId) return i;
        return -1;
    }
    static int binarySearch(Vehicle* arr, int size, int targetId) {
        int l = 0, r = size - 1;
        while (l <= r) {
            int m = l + (r - l) / 2;
            if (arr[m].id == targetId) return m;
            if (arr[m].id < targetId) l = m + 1; else r = m - 1;
        }
        return -1;
    }
    static void bubbleSort(Vehicle* arr, int size) {
        for (int i = 0; i < size - 1; i++)
            for (int j = 0; j < size - i - 1; j++)
                if (arr[j].id > arr[j + 1].id) swap(arr[j], arr[j + 1]);
    }
    static void quickSort(Vehicle* arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }
    static int partition(Vehicle* arr, int low, int high) {
        float pivot = arr[high].price; int i = low - 1;
        for (int j = low; j < high; j++)
            if (arr[j].price <= pivot) { i++; swap(arr[i], arr[j]); }
        swap(arr[i + 1], arr[high]); return i + 1;
    }
    static void mergeSort(Vehicle* arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m); mergeSort(arr, m + 1, r); merge(arr, l, m, r);
        }
    }
    static void merge(Vehicle* arr, int l, int m, int r) {
        int n1 = m - l + 1, n2 = r - m;
        Vehicle* L = new Vehicle[n1], *R = new Vehicle[n2];
        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) arr[k++] = (L[i].name <= R[j].name) ? L[i++] : R[j++];
        while (i < n1) arr[k++] = L[i++];
        while (j < n2) arr[k++] = R[j++];
        delete[] L; delete[] R;
    }
};

// ====== Hash Table for Vehicles ======
class HashTable {
    static const int TABLE_SIZE = 101;
    struct Node { int key; Vehicle* value; Node* next; Node(int k, Vehicle* v) : key(k), value(v), next(nullptr) {} };
    Node* table[TABLE_SIZE];
    int hash(int key) const { return key % TABLE_SIZE; }
public:
    HashTable() { for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr; }
    ~HashTable() { clear(); }
    void insert(int key, Vehicle* value) {
        int idx = hash(key);
        Node* n = new Node(key, value);
        n->next = table[idx]; table[idx] = n;
    }
    Vehicle* search(int key) {
        Node* curr = table[hash(key)];
        while (curr) { if (curr->key == key) return curr->value; curr = curr->next; }
        return nullptr;
    }
    void clear() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            Node* curr = table[i];
            while (curr) { Node* t = curr; curr = curr->next; delete t; }
            table[i] = nullptr;
        }
    }
};

// ====== Globals & Utility ======
VehicleLinkedList vehicleList;
HashTable vehicleHash;
Stack<Transaction> transactionStack;
Queue<Customer> customerQueue;
int totalVehicles = 0;

void displayMainMenu() {
    cout << "\n===== DEEP COMPANY MANAGEMENT SYSTEM =====\n"
         << "1. View all vehicles\n2. Buy a vehicle\n3. Rent a vehicle\n4. Return a rented vehicle\n"
         << "5. Add a new vehicle\n6. Update vehicle availability\n7. Search vehicles\n8. Sort vehicles\n"
         << "9. View transaction history\n10. View customer queue\n11. Exit\nEnter your choice: ";
}
void clearScreen() { cout << "\n[Screen cleared]\n\n"; }
Date readDate(const string& prompt) {
    int d, m, y; cout << prompt << " (DD MM YYYY): "; cin >> d >> m >> y; return Date(d, m, y);
}
void initializeData() {
    Vehicle v[] = {
        Vehicle("Suzuki Alto", 2024, 7400.0f, 2025001, 35.0f, "Suzuki", 2024, true, true, Date(15, 6, 2024)),
        Vehicle("Hyundai Accent", 2020, 10500.0f, 2025002, 45.0f, "Hyundai", 2020, true, true, Date(10, 7, 2020)),
        Vehicle("Toyota Yaris", 2018, 12000.0f, 2025003, 50.0f, "Toyota", 2018, true, true, Date(5, 3, 2018)),
        Vehicle("Kia Picanto", 2023, 10499.0f, 2025004, 40.0f, "Kia", 2023, true, true, Date(12, 5, 2023)),
        Vehicle("Nissan Sunny", 2024, 13000.0f, 2025005, 55.0f, "Nissan", 2024, true, true, Date(20, 2, 2024)),
        Vehicle("Chevrolet Spark", 2014, 6500.0f, 2025006, 30.0f, "Chevrolet", 2014, false, true, Date(8, 8, 2014)),
        Vehicle("Renault Kwid", 2024, 8500.0f, 2025007, 38.0f, "Renault", 2024, true, true, Date(3, 4, 2024)),
        Vehicle("Ford Mustang Shelby GT", 2025, 29000.0f, 2025008, 120.0f, "Ford", 2025, true, true, Date(15, 1, 2025)),
        Vehicle("Kia Sportage", 2020, 20500.0f, 2025009, 85.0f, "Kia", 2020, true, false, Date(25, 9, 2020)),
        Vehicle("Hyundai Accent", 2024, 13500.0f, 2025010, 52.0f, "Hyundai", 2024, true, true, Date(17, 11, 2024))
    };
    for (int i = 0; i < 10; i++) {
        vehicleList.insert(v[i]);
        vehicleHash.insert(v[i].id, vehicleList.search(v[i].id));
        totalVehicles++;
    }
}

// ====== Main ======
int main() {
    try {
        initializeData();
        int choice; bool exit = false;
        cout << "Welcome to Deep Company!" << endl;
        cout << "Total vehicles in inventory: " << totalVehicles << endl;

        while (!exit) {
            displayMainMenu();
            cin >> choice;
            switch (choice) {
            case 1: { // View all vehicles
                clearScreen();
                cout << "\n===== VEHICLE INVENTORY (LINKED LIST) =====\n"
                     << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price" << setw(10) << "ID"
                     << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                     << string(90, '-') << endl;
                vehicleList.displayAll(); break;
            }
            case 2: { // Buy a vehicle
                clearScreen();
                cout << "\n===== AVAILABLE VEHICLES FOR SALE =====\n"
                     << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price" << setw(10) << "ID"
                     << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                     << string(90, '-') << endl;
                vehicleList.displayFiltered(true, false);
                int selectedId;
                cout << "\nEnter the ID of the car you want to buy (0 to cancel): "; cin >> selectedId;
                if (selectedId == 0) { cout << "Purchase cancelled." << endl; break; }
                try {
                    Vehicle* v = vehicleHash.search(selectedId);
                    if (!v) throw runtime_error("Sorry, car not found.");
                    if (!v->isAvailableForSale) throw runtime_error("Sorry, this car is not available for sale.");
                    Customer customer; customer.input(); customerQueue.enqueue(customer);
                    clearScreen();
                    char payType;
                    cout << "Do you want to pay Cash or Installments? (C/I): "; cin >> payType;
                    Date currentDate;
                    Transaction sale(customer, *v, currentDate, currentDate, 'S');
                    transactionStack.push(sale);
                    sale.displayReceipt();
                    vehicleList.updateAvailability(selectedId, false, false);
                    cout << "\nPurchase completed successfully!" << endl;
                } catch (const exception& e) { cout << "Error: " << e.what() << endl; }
                break;
            }
            case 3: { // Rent a vehicle
                clearScreen();
                cout << "\n===== AVAILABLE VEHICLES FOR RENT =====\n"
                     << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price" << setw(10) << "ID"
                     << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                     << string(90, '-') << endl;
                vehicleList.displayFiltered(false, true);
                int selectedId;
                cout << "\nEnter the ID of the car you want to rent (0 to cancel): "; cin >> selectedId;
                if (selectedId == 0) { cout << "Rental cancelled." << endl; break; }
                try {
                    Vehicle* v = vehicleHash.search(selectedId);
                    if (!v) throw runtime_error("Sorry, car not found.");
                    if (!v->isAvailableForRent) throw runtime_error("Sorry, this car is not available for rent.");
                    Customer customer; customer.input(); customerQueue.enqueue(customer);
                    clearScreen();
                    Date start = readDate("Enter start date"), end = readDate("Enter end date");
                    Transaction rent(customer, *v, start, end, 'R');
                    transactionStack.push(rent);
                    vehicleList.updateAvailability(selectedId, false, false);
                    rent.displayReceipt();
                    cout << "\nRental completed successfully!" << endl;
                } catch (const exception& e) { cout << "Error: " << e.what() << endl; }
                break;
            }
            case 4: { // Return rented vehicle
                clearScreen();
                cout << "\n===== RETURN A RENTED VEHICLE =====\n";
                if (transactionStack.isEmpty()) { cout << "No transactions available." << endl; break; }
                cout << "Most recent transaction:" << endl;
                Transaction recent = transactionStack.peek();
                recent.displayReceipt();
                char confirm;
                cout << "Complete this transaction? (Y/N): "; cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') { transactionStack.pop(); cout << "Transaction completed successfully!" << endl; }
                else cout << "Return cancelled." << endl;
                break;
            }
            case 5: { // Add new vehicle
                clearScreen();
                cout << "\n===== ADD NEW VEHICLE =====\n";
                string name, manufacturer; int model, year, id; float price, rentPrice; bool forSale, forRent;
                cout << "Enter car name: "; cin.ignore(); getline(cin, name);
                cout << "Enter manufacturer: "; getline(cin, manufacturer);
                cout << "Enter model year: "; cin >> model;
                cout << "Enter manufacturing year: "; cin >> year;
                cout << "Enter price: $"; cin >> price;
                cout << "Enter rent price per day: $"; cin >> rentPrice;
                cout << "Enter ID: "; cin >> id;
                cout << "Available for sale? (1/0): "; cin >> forSale;
                cout << "Available for rent? (1/0): "; cin >> forRent;
                Date manufactureDate = readDate("Enter manufacture date");
                try {
                    Vehicle newVehicle(name, model, price, id, rentPrice, manufacturer, year, forRent, forSale, manufactureDate);
                    vehicleList.insert(newVehicle);
                    vehicleHash.insert(id, vehicleList.search(id));
                    totalVehicles++;
                    cout << "New vehicle added successfully!" << endl;
                } catch (const exception& e) { cout << "Error: " << e.what() << endl; }
                break;
            }
            case 6: { // Update vehicle availability
                clearScreen();
                cout << "\n===== UPDATE VEHICLE AVAILABILITY =====\n";
                int id; bool forSale, forRent;
                cout << "Enter vehicle ID: "; cin >> id;
                cout << "Available for sale? (1/0): "; cin >> forSale;
                cout << "Available for rent? (1/0): "; cin >> forRent;
                if (vehicleList.updateAvailability(id, forSale, forRent)) cout << "Vehicle availability updated successfully!" << endl;
                else cout << "Vehicle not found!" << endl;
                break;
            }
            case 7: { // Search vehicles
                clearScreen();
                cout << "\n===== SEARCH VEHICLES =====\n"
                     << "1. Linear Search by ID\n2. Binary Search by ID (requires sorted data)\n3. Hash Table Search by ID\nEnter search method: ";
                int searchChoice, searchId; cin >> searchChoice;
                cout << "Enter vehicle ID to search: "; cin >> searchId;
                switch (searchChoice) {
                case 1: {
                    Vehicle* arr = vehicleList.toArray(); int size = vehicleList.getSize();
                    int idx = SearchSort::linearSearch(arr, size, searchId);
                    if (idx != -1) {
                        cout << "\nVehicle found using Linear Search at index " << idx << ":\n"
                             << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price"
                             << setw(10) << "ID" << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                             << string(90, '-') << endl;
                        arr[idx].display();
                    } else cout << "Vehicle not found using Linear Search." << endl;
                    delete[] arr; break;
                }
                case 2: {
                    Vehicle* arr = vehicleList.toArray(); int size = vehicleList.getSize();
                    SearchSort::bubbleSort(arr, size);
                    int idx = SearchSort::binarySearch(arr, size, searchId);
                    if (idx != -1) {
                        cout << "\nVehicle found using Binary Search at index " << idx << ":\n"
                             << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price"
                             << setw(10) << "ID" << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                             << string(90, '-') << endl;
                        arr[idx].display();
                    } else cout << "Vehicle not found using Binary Search." << endl;
                    delete[] arr; break;
                }
                case 3: {
                    Vehicle* v = vehicleHash.search(searchId);
                    if (v) {
                        cout << "\nVehicle found using Hash Table Search:\n"
                             << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price"
                             << setw(10) << "ID" << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                             << string(90, '-') << endl;
                        v->display();
                    } else cout << "Vehicle not found using Hash Table Search." << endl;
                    break;
                }
                default: cout << "Invalid search method!" << endl;
                }
                break;
            }
            case 8: { // Sort vehicles
                clearScreen();
                cout << "\n===== SORT VEHICLES =====\n"
                     << "1. Bubble Sort by ID\n2. Quick Sort by Price\n3. Merge Sort by Name\nEnter sorting method: ";
                int sortChoice; cin >> sortChoice;
                Vehicle* arr = vehicleList.toArray(); int size = vehicleList.getSize();
                if (!arr || size == 0) { cout << "No vehicles to sort!" << endl; break; }
                switch (sortChoice) {
                case 1: SearchSort::bubbleSort(arr, size); cout << "\nVehicles sorted by ID using Bubble Sort:\n"; break;
                case 2: SearchSort::quickSort(arr, 0, size - 1); cout << "\nVehicles sorted by Price using Quick Sort:\n"; break;
                case 3: SearchSort::mergeSort(arr, 0, size - 1); cout << "\nVehicles sorted by Name using Merge Sort:\n"; break;
                default: cout << "Invalid sorting method!" << endl; delete[] arr; break;
                }
                if (sortChoice >= 1 && sortChoice <= 3) {
                    cout << left << setw(25) << "Car Name" << setw(10) << "Model" << setw(10) << "Price"
                         << setw(10) << "ID" << setw(15) << "Rent Price/Day" << setw(10) << "For Sale" << setw(10) << "For Rent" << endl
                         << string(90, '-') << endl;
                    for (int i = 0; i < size; i++) arr[i].display();
                }
                delete[] arr;
                break;
            }
            case 9: { // Transaction history
                clearScreen();
                cout << "\n===== TRANSACTION HISTORY (STACK) =====\n";
                if (transactionStack.isEmpty()) cout << "No transactions available." << endl;
                else transactionStack.display();
                break;
            }
            case 10: { // Customer queue
                clearScreen();
                cout << "\n===== CUSTOMER QUEUE =====\n";
                if (customerQueue.isEmpty()) cout << "No customers in queue." << endl;
                else { customerQueue.display(); cout << "\nTotal customers in queue: " << customerQueue.getSize() << endl; }
                break;
            }
            case 11:
                exit = true;
                cout << "\nThank you for using Deep Company Management System!" << endl;
                cout << "Data Structures used:\n- Linked List for vehicle inventory\n- Stack for transaction history\n- Queue for customer management\n- Hash Table for fast vehicle lookup\n- Various sorting and searching algorithms\n";
                break;
            default: cout << "Invalid choice! Please try again." << endl;
            }
        }
    } catch (const exception& e) { cout << "Critical error: " << e.what() << endl; }
    return 0;
}