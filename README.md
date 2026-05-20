# Vehicle Rental Management System

A comprehensive C++ application for managing vehicle rental and sales operations with advanced data structures and algorithms. Perfect for learning data structures, algorithms, and system design.

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Highlights](#project-highlights)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [System Architecture](#system-architecture)
- [Data Structures](#data-structures)
- [Algorithms Implemented](#algorithms-implemented)
- [Menu Guide](#menu-guide)
- [Code Examples](#code-examples)
- [Sample Data](#sample-data)
- [Time Complexity Analysis](#time-complexity-analysis)
- [Contributing](#contributing)
- [License](#license)

## Overview

Deep Company Management System is a full-featured vehicle rental and sales management platform. It demonstrates the practical application of fundamental data structures and algorithms in a real-world business scenario. The system handles vehicle inventory, customer transactions, and provides powerful search and sorting capabilities.

## Features

🚗 **Vehicle Management**
- View complete vehicle inventory
- Add new vehicles to inventory
- Update vehicle availability status
- Filter vehicles by sale/rental availability

💳 **Transaction Processing**
- Buy vehicles with payment options (Cash/Installments)
- Rent vehicles with customizable date ranges
- Automatic rental cost calculation
- Generate professional receipts and invoices

🔍 **Advanced Search**
- Linear Search for sequential lookup
- Binary Search for sorted data
- Hash Table lookup for O(1) average performance
- Flexible vehicle filtering

📊 **Sorting & Analytics**
- Bubble Sort by vehicle ID
- Quick Sort by price
- Merge Sort by vehicle name
- Real-time inventory display

📋 **Data Management**
- Customer queue management
- Transaction history stack
- Comprehensive record keeping
- Dynamic memory allocation

## Project Highlights

| Feature | Technology |
|---------|-----------|
| **Vehicle Inventory** | Linked List |
| **Transaction History** | Stack (LIFO) |
| **Customer Management** | Queue (FIFO) |
| **Fast Lookup** | Hash Table (Chaining) |
| **Searching** | Linear, Binary Search |
| **Sorting** | Bubble, Quick, Merge Sort |

## Requirements

- **C++ Compiler** - C++11 or later (GCC, Clang, MSVC)
- **Standard Library** - iostream, string, iomanip, algorithm
- **OS** - Windows, macOS, or Linux
- **Memory** - Minimum 50MB for dynamic data structures

## Installation

1. **Clone the repository**
```bash
git clone https://github.com/hamzahmed5/Vehicle-Rental.git
cd Vehicle-Rental
```

2. **Compile the program**
```bash
# Using g++
g++ "Vehicle Rental.C++" -o vehicle_rental

# Using clang++
clang++ "Vehicle Rental.C++" -o vehicle_rental

# Using MSVC (Windows)
cl "Vehicle Rental.C++" /Fe:vehicle_rental.exe
```

3. **Run the application**
```bash
# Linux/macOS
./vehicle_rental

# Windows
vehicle_rental.exe
```

## Usage

Launch the application and interact with the main menu to perform operations:

```
===== DEEP COMPANY MANAGEMENT SYSTEM =====
1. View all vehicles
2. Buy a vehicle
3. Rent a vehicle
4. Return a rented vehicle
5. Add a new vehicle
6. Update vehicle availability
7. Search vehicles
8. Sort vehicles
9. View transaction history
10. View customer queue
11. Exit
```

### Basic Workflow

**To Buy a Vehicle:**
1. Select option 2 from menu
2. View available vehicles for sale
3. Enter vehicle ID
4. Input customer information
5. Choose payment method (Cash or Installments)
6. Receive purchase receipt

**To Rent a Vehicle:**
1. Select option 3 from menu
2. View available vehicles for rent
3. Enter vehicle ID
4. Input customer information
5. Specify rental start and end dates
6. Receive rental receipt with total cost

**To Search Vehicles:**
1. Select option 7 from menu
2. Choose search method:
   - Linear Search (searches through all vehicles)
   - Binary Search (requires sorted data)
   - Hash Table Search (fastest, O(1) average)
3. Enter vehicle ID
4. View results instantly

## System Architecture

### Core Components

```
┌─────────────────────────────────────────────────┐
│      Main Menu & User Interface                 │
├─────────────────────────────────────────────────┤
│  ┌──────────────┐  ┌──────────────┐            │
│  │  Operations  │  │   Search &   │            │
│  │ (Buy/Rent)   │  │    Sort      │            │
│  └──────────────┘  └──────────────┘            │
├─────────────────────────────────────────────────┤
│          Data Structure Layer                   │
│  ┌──────────┐ ┌────────┐ ┌──────┐ ┌────────┐  │
│  │Linked    │ │ Stack  │ │Queue │ │ Hash   │  │
│  │List      │ │(Trans) │ │(Cust)│ │Table   │  │
│  └──────────┘ └────────┘ └──────┘ └────────┘  │
├─────────────────────────────────────────────────┤
│     Algorithms (Search, Sort, Hash)             │
└─────────────────────────────────────────────────┘
```

## Data Structures

### 1. **Vehicle Linked List**
Maintains the primary inventory using a singly linked list:
```cpp
struct Vehicle {
    string name, manufacturer;
    int model, year, id;
    float price, rentPricePerDay;
    bool isAvailableForRent, isAvailableForSale;
    Date manufactureDate;
};

class VehicleLinkedList {
    - insert(Vehicle)
    - remove(int id)
    - search(int id)
    - displayAll()
    - updateAvailability()
};
```

**Operations:**
- Insert: O(n)
- Delete: O(n)
- Search: O(n)
- Display: O(n)

### 2. **Transaction Stack**
LIFO structure for managing transaction history:
```cpp
Stack<Transaction> transactionStack;

Operations:
- push(Transaction)    // O(1)
- pop()               // O(1)
- peek()              // O(1)
- isEmpty()           // O(1)
```

### 3. **Customer Queue**
FIFO structure for customer management:
```cpp
Queue<Customer> customerQueue;

Operations:
- enqueue(Customer)   // O(1)
- dequeue()          // O(1)
- getFront()         // O(1)
- isEmpty()          // O(1)
```

### 4. **Vehicle Hash Table**
Fast lookup using hash table with chaining:
```cpp
class HashTable {
    static const int TABLE_SIZE = 101;
    Node* table[TABLE_SIZE];
    
Operations:
- insert(key, value)  // O(1) average
- search(key)         // O(1) average
- clear()            // O(n)
};
```

## Algorithms Implemented

### Searching Algorithms

**Linear Search**
```cpp
static int linearSearch(Vehicle* arr, int size, int targetId)
// Time: O(n), Space: O(1)
// Best for: Small datasets or unsorted arrays
```

**Binary Search**
```cpp
static int binarySearch(Vehicle* arr, int size, int targetId)
// Time: O(log n), Space: O(1)
// Prerequisite: Array must be sorted
// Best for: Large sorted datasets
```

### Sorting Algorithms

**Bubble Sort**
```cpp
static void bubbleSort(Vehicle* arr, int size)
// Time: O(n²), Space: O(1)
// Sorts by vehicle ID
```

**Quick Sort**
```cpp
static void quickSort(Vehicle* arr, int low, int high)
// Time: O(n log n) average, O(n²) worst
// Space: O(log n) recursion
// Sorts by vehicle price (pivot-based partitioning)
```

**Merge Sort**
```cpp
static void mergeSort(Vehicle* arr, int l, int r)
// Time: O(n log n), Space: O(n)
// Stable sort by vehicle name
```

## Menu Guide

### Option 1: View All Vehicles
Displays the complete vehicle inventory with:
- Vehicle name, model, and manufacturing year
- Price and rental rate
- Vehicle ID
- Availability status (for sale/rent)

### Option 2: Buy a Vehicle
Purchase workflow:
- Shows available vehicles for sale
- Validates vehicle existence and availability
- Collects customer information
- Processes payment
- Generates purchase invoice

### Option 3: Rent a Vehicle
Rental workflow:
- Shows available vehicles for rent
- Prompts for rental duration
- Calculates total rental cost
- Records transaction in stack
- Generates rental receipt

### Option 4: Return Rented Vehicle
- Displays most recent rental transaction
- Allows completion confirmation
- Updates vehicle availability

### Option 5: Add New Vehicle
Dynamic inventory expansion:
- Input vehicle specifications
- Set rental and sale pricing
- Define manufacturing date
- Automatic ID assignment

### Option 6: Update Availability
Modify vehicle status:
- Toggle sale availability
- Toggle rental availability
- Updates both linked list and hash table

### Option 7: Search Vehicles
Three search methods:
1. **Linear Search** - Sequential search O(n)
2. **Binary Search** - Requires sorting, O(log n)
3. **Hash Table** - Direct lookup, O(1) average

### Option 8: Sort Vehicles
Three sorting algorithms:
1. **Bubble Sort** - By ID, educational algorithm
2. **Quick Sort** - By Price, divide-and-conquer
3. **Merge Sort** - By Name, stable sort

### Option 9: View Transaction History
Stack-based display showing:
- All completed transactions
- Transaction IDs
- LIFO order (most recent first)

### Option 10: View Customer Queue
Shows:
- All customers in queue
- Customer count
- FIFO order (first arrived first)

### Option 11: Exit
Displays system summary and closes application

## Code Examples

### Example 1: Create and Add a Vehicle
```cpp
Vehicle newCar("Toyota Corolla", 2024, 15000.0f, 2025011, 
               60.0f, "Toyota", 2024, true, true, 
               Date(10, 5, 2024));
vehicleList.insert(newCar);
vehicleHash.insert(newCar.id, vehicleList.search(newCar.id));
```

### Example 2: Process a Rental Transaction
```cpp
Customer customer;
customer.input();
customerQueue.enqueue(customer);

Date startDate(15, 6, 2025);
Date endDate(20, 6, 2025);
Vehicle* rentedVehicle = vehicleHash.search(vehicleId);

Transaction rental(customer, *rentedVehicle, startDate, endDate, 'R');
transactionStack.push(rental);
rental.displayReceipt();
```

### Example 3: Search for a Vehicle
```cpp
Vehicle* arr = vehicleList.toArray();
int size = vehicleList.getSize();

// Using hash table for instant lookup
Vehicle* found = vehicleHash.search(vehicleId);
if (found) {
    found->display();
}
```

## Sample Data

The system initializes with 10 vehicles:

| Vehicle | ID | Price | Rent/Day | Available |
|---------|-----|-------|----------|-----------|
| Suzuki Alto | 2025001 | $7,400 | $35 | ✅ Both |
| Hyundai Accent | 2025002 | $10,500 | $45 | ✅ Both |
| Toyota Yaris | 2025003 | $12,000 | $50 | ✅ Both |
| Kia Picanto | 2025004 | $10,499 | $40 | ✅ Both |
| Nissan Sunny | 2025005 | $13,000 | $55 | ✅ Both |
| Chevrolet Spark | 2025006 | $6,500 | $30 | ❌ Sale Only |
| Renault Kwid | 2025007 | $8,500 | $38 | ✅ Both |
| Ford Mustang Shelby GT | 2025008 | $29,000 | $120 | ✅ Both |
| Kia Sportage | 2025009 | $20,500 | $85 | ✅ Rent Only |
| Hyundai Accent | 2025010 | $13,500 | $52 | ✅ Both |

## Time Complexity Analysis

| Operation | Linked List | Stack | Queue | Hash Table |
|-----------|------------|-------|-------|-----------|
| Insert | O(n) | O(1) | O(1) | O(1) avg |
| Delete | O(n) | O(1) | O(1) | O(1) avg |
| Search | O(n) | - | - | O(1) avg |
| Display | O(n) | O(n) | O(n) | O(n) |
| Update | O(n) | - | - | O(1) avg |

### Algorithm Complexity

| Algorithm | Best | Average | Worst | Space |
|-----------|------|---------|-------|-------|
| Linear Search | O(1) | O(n) | O(n) | O(1) |
| Binary Search | O(1) | O(log n) | O(log n) | O(1) |
| Bubble Sort | O(n) | O(n²) | O(n²) | O(1) |
| Quick Sort | O(n log n) | O(n log n) | O(n²) | O(log n) |
| Merge Sort | O(n log n) | O(n log n) | O(n log n) | O(n) |

## Future Enhancements

- [ ] **Persistent Storage** - Save/load data from files (JSON/CSV)
- [ ] **Database Integration** - MySQL/SQLite backend
- [ ] **GUI Interface** - Qt or SFML based graphical interface
- [ ] **Advanced Filtering** - Filter by price range, age, condition
- [ ] **Customer Accounts** - User login and personalized history
- [ ] **Reservation System** - Book vehicles in advance
- [ ] **Reporting** - Generate sales and revenue reports
- [ ] **Payment Gateway** - Integrate online payment processing
- [ ] **Vehicle Maintenance** - Track service history
- [ ] **Insurance Module** - Calculate and manage insurance
- [ ] **Mobile App** - Cross-platform mobile application
- [ ] **Email Notifications** - Automated booking confirmations

## Technical Details

**Memory Management:**
- Dynamic arrays for sorting operations
- Proper deallocation of linked list nodes
- Stack and queue memory cleanup

**Error Handling:**
- Exception handling with try-catch blocks
- Runtime error checks for empty collections
- Vehicle availability validation

**Code Organization:**
- Modular functions for each operation
- Separate data structure classes
- Template-based generic containers (Stack, Queue)

## Contributing

Contributions are welcome! Feel free to:
- Report bugs and issues
- Suggest new features
- Submit pull requests for improvements
- Improve documentation

### Contribution Guidelines
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/enhancement`)
3. Commit your changes (`git commit -m 'Add new feature'`)
4. Push to the branch (`git push origin feature/enhancement`)
5. Open a Pull Request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

---

**Project Type**: Educational | Data Structures & Algorithms  
**Author**: [Your Name]  
**Created**: 2025  
**Status**: ✅ Fully Functional  
**Difficulty**: Intermediate to Advanced

### Learning Outcomes
- Master fundamental data structures
- Understand algorithm complexity analysis
- Apply real-world problem-solving
- Practice memory management in C++
- Design scalable systems

---

**Key Takeaways:**
This project demonstrates the importance of choosing the right data structure for each use case. The combination of Linked List, Stack, Queue, and Hash Table provides an efficient and flexible solution for a business management system.
