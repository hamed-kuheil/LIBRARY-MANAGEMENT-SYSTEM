// =============================================================================
// Library Management System
// Final Project - Data Structures using C++
// Data Structures Used:
// 1. Doubly Linked List
// 2. Binary Search Tree (BST)
// 3. Queue
// 4. Stack
// =============================================================================

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// =============================================================================
// Queue
// =============================================================================

struct QueueNode {
    string studentName;
    QueueNode* next;

    QueueNode(string name) {
        studentName = name;
        next = nullptr;
    }
};

class WaitlistQueue {
private:
    QueueNode* front;
    QueueNode* rear;
    int size;

public:
    WaitlistQueue() {
        front = rear = nullptr;
        size = 0;
    }

    ~WaitlistQueue() {
        while (front) {
            QueueNode* temp = front;
            front = front->next;
            delete temp;
        }
    }

    void enqueue(string name) {
        QueueNode* newNode = new QueueNode(name);

        if (!rear) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        size++;
    }

    string dequeue() {
        if (!front) return "";

        QueueNode* temp = front;
        string name = temp->studentName;

        front = front->next;

        if (!front)
            rear = nullptr;

        delete temp;
        size--;

        return name;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    int getSize() {
        return size;
    }

    void display() {
        if (isEmpty()) {
            cout << "No students in waitlist.\n";
            return;
        }

        QueueNode* current = front;
        int position = 1;

        while (current) {
            cout << position++ << ". "
                 << current->studentName << endl;
            current = current->next;
        }
    }
};

// =============================================================================
// Book
// =============================================================================

class Book {
private:
    int id;
    string title;
    string author;
    bool available;
    string borrowedBy;

public:
    WaitlistQueue waitlist;

    Book(int i, string t, string a) {
        id = i;
        title = t;
        author = a;
        available = true;
        borrowedBy = "";
    }

    int getID() {
        return id;
    }

    string getTitle() {
        return title;
    }

    string getAuthor() {
        return author;
    }

    bool isAvailable() {
        return available;
    }

    string getBorrowedBy() {
        return borrowedBy;
    }

    bool borrowBook(string student) {
        if (available) {
            available = false;
            borrowedBy = student;
            return true;
        }

        return false;
    }

    string returnBook() {
        available = true;
        borrowedBy = "";

        if (!waitlist.isEmpty()) {
            string nextStudent = waitlist.dequeue();
            available = false;
            borrowedBy = nextStudent;
            return nextStudent;
        }

        return "";
    }
};

// =============================================================================
// Doubly Linked List
// =============================================================================

struct DLLNode {
    Book book;
    DLLNode* next;
    DLLNode* prev;

    DLLNode(int id, string title, string author)
        : book(id, title, author) {

        next = prev = nullptr;
    }
};

class DoublyLinkedList {
private:
    DLLNode* head;
    DLLNode* tail;

public:
    DoublyLinkedList() {
        head = tail = nullptr;
    }

    ~DoublyLinkedList() {
        DLLNode* current = head;

        while (current) {
            DLLNode* temp = current;
            current = current->next;
            delete temp;
        }
    }

    DLLNode* addBook(int id, string title, string author) {
        DLLNode* newNode = new DLLNode(id, title, author);

        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        return newNode;
    }

    bool removeBook(DLLNode* node) {
        if (!node) return false;

        if (node == head)
            head = head->next;
        else
            node->prev->next = node->next;

        if (node == tail)
            tail = tail->prev;
        else
            node->next->prev = node->prev;

        delete node;

        return true;
    }

    DLLNode* getHead() {
        return head;
    }

    DLLNode* searchByTitle(string title) {
        DLLNode* current = head;

        while (current) {
            if (current->book.getTitle() == title)
                return current;

            current = current->next;
        }

        return nullptr;
    }
};

// =============================================================================
// BST
// =============================================================================

struct BSTNode {
    int id;
    DLLNode* bookPtr;
    BSTNode* left;
    BSTNode* right;

    BSTNode(int i, DLLNode* ptr) {
        id = i;
        bookPtr = ptr;
        left = right = nullptr;
    }
};

class BST {
private:
    BSTNode* root;

    BSTNode* insertHelper(BSTNode* node, int id, DLLNode* ptr) {
        if (!node)
            return new BSTNode(id, ptr);

        if (id < node->id)
            node->left = insertHelper(node->left, id, ptr);

        else if (id > node->id)
            node->right = insertHelper(node->right, id, ptr);

        return node;
    }

    DLLNode* searchHelper(BSTNode* node, int id) {
        if (!node)
            return nullptr;

        if (node->id == id)
            return node->bookPtr;

        if (id < node->id)
            return searchHelper(node->left, id);

        return searchHelper(node->right, id);
    }

    BSTNode* findMin(BSTNode* node) {
        while (node->left)
            node = node->left;

        return node;
    }

    BSTNode* removeHelper(BSTNode* node, int id) {
        if (!node)
            return nullptr;

        if (id < node->id)
            node->left = removeHelper(node->left, id);

        else if (id > node->id)
            node->right = removeHelper(node->right, id);

        else {
            if (!node->left) {
                BSTNode* temp = node->right;
                delete node;
                return temp;
            }

            else if (!node->right) {
                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            BSTNode* temp = findMin(node->right);

            node->id = temp->id;
            node->bookPtr = temp->bookPtr;

            node->right = removeHelper(node->right, temp->id);
        }

        return node;
    }

    void destroy(BSTNode* node) {
        if (!node) return;

        destroy(node->left);
        destroy(node->right);

        delete node;
    }

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        destroy(root);
    }

    void insert(int id, DLLNode* ptr) {
        root = insertHelper(root, id, ptr);
    }

    DLLNode* search(int id) {
        return searchHelper(root, id);
    }

    void remove(int id) {
        root = removeHelper(root, id);
    }
};

// =============================================================================
// Stack
// =============================================================================

struct Transaction {
    int bookID;
    string studentName;
};

struct StackNode {
    Transaction data;
    StackNode* next;

    StackNode(Transaction t) {
        data = t;
        next = nullptr;
    }
};

class TransactionStack {
private:
    StackNode* top;

public:
    TransactionStack() {
        top = nullptr;
    }

    ~TransactionStack() {
        while (top) {
            StackNode* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(Transaction t) {
        StackNode* newNode = new StackNode(t);

        newNode->next = top;
        top = newNode;
    }

    bool pop(Transaction& t) {
        if (!top)
            return false;

        StackNode* temp = top;

        t = temp->data;
        top = top->next;

        delete temp;

        return true;
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

// =============================================================================
// Library System
// =============================================================================

class LibrarySystem {
private:
    DoublyLinkedList catalog;
    BST index;
    TransactionStack transactions;

public:
    void addBook(int id, string title, string author) {

        if (index.search(id)) {
            cout << "Book ID already exists.\n";
            return;
        }

        DLLNode* node = catalog.addBook(id, title, author);

        index.insert(id, node);

        cout << "Book added successfully.\n";
    }

    void displayBooks() {

        DLLNode* current = catalog.getHead();

        if (!current) {
            cout << "No books available.\n";
            return;
        }

        cout << "\n";
        cout << left
             << setw(10) << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << endl;

        cout << string(80, '-') << endl;

        while (current) {

            cout << left
                 << setw(10) << current->book.getID()
                 << setw(30) << current->book.getTitle()
                 << setw(25) << current->book.getAuthor();

            if (current->book.isAvailable())
                cout << setw(15) << "Available";
            else
                cout << setw(15) << "Borrowed";

            cout << endl;

            current = current->next;
        }
    }
};

int main() {

    LibrarySystem library;

    library.addBook(101, "Clean Code", "Robert Martin");
    library.addBook(102, "Data Structures", "Mark Allen");

    library.displayBooks();

    return 0;
}
