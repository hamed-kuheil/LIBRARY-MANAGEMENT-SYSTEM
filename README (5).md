# 📚 Advanced Library Management System

A complete command-line based **Library Management System** developed for the **Data Structures** course using pure **C++17** and fully custom-built data structures without using STL containers such as `vector`, `list`, `queue`, `stack`, or `map`.

The project demonstrates how multiple data structures can work together efficiently inside one integrated system.

---

# 👨‍🏫 Academic Supervision

- **Dr. M Islam Abbasi**

---

# 👥 Team Information

| Role | Student Name | University ID |
|------|---------------|----------------|
| Team Lead | Hamed Kuheil | 71590 |
| Member 1 | Mohammed Kuheil | 71593 |
| Member 2 | Mahmoud Kuheil | 71597 |

---

# 🧠 Data Structures Used

## 1. Doubly Linked List (DLL)
Used as the main library catalog.

### Responsibilities
- Store all books dynamically
- Fast insertion and deletion
- Forward and backward traversal

---

## 2. Binary Search Tree (BST)
Used for fast indexing and searching by Book ID.

### Responsibilities
- O(log n) average search complexity
- Direct pointer mapping to linked list nodes
- Efficient lookup and removal operations

---

## 3. Queue (FIFO Waitlist)
Each book owns a custom queue for student waitlists.

### Responsibilities
- Manage students waiting for unavailable books
- First-In First-Out processing
- Automatic assignment after return

---

## 4. Stack (Transaction History)
Used to support the Undo Borrow operation.

### Responsibilities
- Store borrowing transactions
- Reverse the latest borrow operation
- Last-In First-Out behavior

---

# ✨ System Features

- Add new books
- Remove books safely
- Search books by ID
- Borrow books
- Return books
- Automatic waitlist handling
- Undo last borrow transaction
- View all books
- Update book information
- View transaction history
- Display BST indexed IDs
- Full input validation
- Dynamic memory management
- Zero memory leaks

---

# ⚙️ System Architecture

The system combines all structures together:

BST Node → points directly to → Doubly Linked List Book Node

This design improves search performance while keeping insertion and deletion efficient.

Each book object also contains:
- Its own waitlist queue
- Borrowing status
- Borrower information

A global stack stores transaction history for rollback operations.

---

# 📊 Time Complexity Analysis

| Operation | Data Structure | Complexity |
|-----------|----------------|------------|
| Add Book | DLL + BST | O(log n) |
| Remove Book | BST + DLL | O(log n) |
| Search Book by ID | BST | O(log n) |
| Display All Books | DLL | O(n) |
| Borrow Book | BST + Queue | O(log n) |
| Return Book | BST + Queue | O(log n) |
| Waitlist Enqueue | Queue | O(1) |
| Waitlist Dequeue | Queue | O(1) |
| Undo Last Borrow | Stack | O(1) |
| View Transactions | Stack | O(n) |

---

# 🔒 Memory Management

All data structures implement proper destructors to safely release dynamically allocated memory.

The project avoids:
- Memory leaks
- Dangling pointers
- Shallow copy corruption

---

# 💻 Technologies Used

- C++17
- Object-Oriented Programming (OOP)
- Dynamic Memory Allocation
- Pure Custom Data Structures
- CLI (Console-Based Interface)

---

# 🚀 How to Compile and Run

## Compile
```bash
g++ LibraryManagementSystem.cpp -o LibrarySystem
```

## Run
### Linux / macOS
```bash
./LibrarySystem
```

### Windows
```bash
LibrarySystem.exe
```

---

# 📁 Project Structure

```text
LibraryManagementSystem.cpp
README.md
```

---

# 📌 Notes

- No GUI was used
- No database was used
- No external libraries were used
- No STL containers were used
- Fully console-based implementation
- Entire system implemented from scratch

---

# ✅ Course Concepts Covered

- Doubly Linked Lists
- Binary Search Trees
- Queues
- Stacks
- Dynamic Memory Allocation
- Object-Oriented Design
- Pointer Manipulation
- Time Complexity Analysis
- Data Structure Integration

---

# 📄 License

This project was developed for academic and educational purposes only.
