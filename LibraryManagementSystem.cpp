#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

// ================= QUEUE =================
struct QNode {
    string name;
    QNode* next;

    QNode(string n) {
        name = n;
        next = nullptr;
    }
};

class Queue {
    QNode *front, *rear;

public:
    Queue() {
        front = rear = nullptr;
    }

    void enqueue(string name) {
        QNode* n = new QNode(name);

        if (!rear)
            front = rear = n;
        else {
            rear->next = n;
            rear = n;
        }
    }

    string dequeue() {
        if (!front)
            return "";

        QNode* temp = front;
        string name = temp->name;

        front = front->next;

        if (!front)
            rear = nullptr;

        delete temp;
        return name;
    }

    bool empty() {
        return front == nullptr;
    }

    void display() {
        QNode* cur = front;
        int i = 1;

        while (cur) {
            cout << i++ << ". " << cur->name << endl;
            cur = cur->next;
        }

        if (!front)
            cout << "Waitlist empty\n";
    }
};

// ================= BOOK =================
class Book {
    int id;
    string title, author;
    bool available;
    string borrower;

public:
    Queue waitlist;

    Book(int i = 0, string t = "", string a = "") {
        id = i;
        title = t;
        author = a;
        available = true;
    }

    int getID() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    bool isAvailable() { return available; }
    string getBorrower() { return borrower; }

    bool borrow(string student) {
        if (!available)
            return false;

        available = false;
        borrower = student;
        return true;
    }

    string giveBack() {
        available = true;
        borrower = "";

        if (!waitlist.empty()) {
            borrower = waitlist.dequeue();
            available = false;
            return borrower;
        }

        return "";
    }
};

// ================= DOUBLY LINKED LIST =================
struct DLL {
    Book book;
    DLL *next, *prev;

    DLL(int id, string t, string a) : book(id, t, a) {
        next = prev = nullptr;
    }
};

class List {
    DLL *head, *tail;

public:
    List() {
        head = tail = nullptr;
    }

    DLL* add(int id, string t, string a) {
        DLL* n = new DLL(id, t, a);

        if (!head)
            head = tail = n;
        else {
            tail->next = n;
            n->prev = tail;
            tail = n;
        }

        return n;
    }

    void remove(DLL* node) {
        if (!node)
            return;

        if (node == head)
            head = head->next;
        else
            node->prev->next = node->next;

        if (node == tail)
            tail = tail->prev;
        else if (node->next)
            node->next->prev = node->prev;

        delete node;
    }

    DLL* getHead() {
        return head;
    }
};

// ================= BST =================
struct BST {
    int id;
    DLL* ptr;
    BST *left, *right;

    BST(int i, DLL* p) {
        id = i;
        ptr = p;
        left = right = nullptr;
    }
};

class Tree {
    BST* root;

    BST* insert(BST* node, int id, DLL* ptr) {
        if (!node)
            return new BST(id, ptr);

        if (id < node->id)
            node->left = insert(node->left, id, ptr);
        else if (id > node->id)
            node->right = insert(node->right, id, ptr);

        return node;
    }

    DLL* search(BST* node, int id) {
        if (!node)
            return nullptr;

        if (id == node->id)
            return node->ptr;

        if (id < node->id)
            return search(node->left, id);

        return search(node->right, id);
    }

public:
    Tree() {
        root = nullptr;
    }

    void insert(int id, DLL* ptr) {
        root = insert(root, id, ptr);
    }

    DLL* search(int id) {
        return search(root, id);
    }
};

// ================= STACK =================
struct Transaction {
    int id;
    string student, action;
};

struct SNode {
    Transaction data;
    SNode* next;

    SNode(Transaction t) {
        data = t;
        next = nullptr;
    }
};

class Stack {
    SNode* top;

public:
    Stack() {
        top = nullptr;
    }

    void push(Transaction t) {
        SNode* n = new SNode(t);
        n->next = top;
        top = n;
    }

    void display() {
        if (!top) {
            cout << "No transactions\n";
            return;
        }

        SNode* cur = top;

        while (cur) {
            cout << cur->data.action
                 << " | Book ID: " << cur->data.id
                 << " | Student: " << cur->data.student
                 << endl;

            cur = cur->next;
        }
    }
};

// ================= LIBRARY =================
class Library {
    List books;
    Tree index;
    Stack history;

public:
    void addBook(int id, string t, string a) {
        if (index.search(id)) {
            cout << "Book already exists\n";
            return;
        }

        DLL* n = books.add(id, t, a);
        index.insert(id, n);

        cout << "Book added\n";
    }

    void displayBooks() {
        DLL* cur = books.getHead();

        if (!cur) {
            cout << "No books available\n";
            return;
        }

        cout << left
             << setw(10) << "ID"
             << setw(25) << "Title"
             << setw(20) << "Author"
             << setw(15) << "Status"
             << endl;

        while (cur) {
            cout << left
                 << setw(10) << cur->book.getID()
                 << setw(25) << cur->book.getTitle()
                 << setw(20) << cur->book.getAuthor()
                 << setw(15)
                 << (cur->book.isAvailable() ? "Available" : "Borrowed")
                 << endl;

            cur = cur->next;
        }
    }

    void searchBook(int id) {
        DLL* n = index.search(id);

        if (!n) {
            cout << "Book not found\n";
            return;
        }

        cout << "Title: " << n->book.getTitle() << endl;
        cout << "Author: " << n->book.getAuthor() << endl;
        cout << "Status: "
             << (n->book.isAvailable() ? "Available" : "Borrowed")
             << endl;
    }

    void borrowBook(int id, string student) {
        DLL* n = index.search(id);

        if (!n) {
            cout << "Book not found\n";
            return;
        }

        if (n->book.borrow(student)) {
            cout << "Book borrowed\n";
            history.push({id, student, "Borrowed"});
        }
        else {
            cout << "Book unavailable, added to waitlist\n";
            n->book.waitlist.enqueue(student);
        }
    }

    void returnBook(int id) {
        DLL* n = index.search(id);

        if (!n) {
            cout << "Book not found\n";
            return;
        }

        string oldStudent = n->book.getBorrower();
        string next = n->book.giveBack();

        history.push({id, oldStudent, "Returned"});

        cout << "Book returned\n";

        if (next != "")
            cout << "Automatically issued to " << next << endl;
    }

    void showWaitlist(int id) {
        DLL* n = index.search(id);

        if (!n) {
            cout << "Book not found\n";
            return;
        }

        n->book.waitlist.display();
    }

    void transactions() {
        history.display();
    }
};

// ================= MAIN =================
int main() {

    Library lib;

    // Default Books
    lib.addBook(101, "Clean Code", "Robert Martin");
    lib.addBook(102, "Data Structures", "Mark Allen");

    int ch, id;
    string title, author, student;

    do {
        cout << "\n===== LIBRARY SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Show Waitlist\n";
        cout << "7. Transactions\n";
        cout << "8. Exit\n";
        cout << "Choice: ";

        cin >> ch;
        cin.ignore();

        switch (ch) {

        case 1:
            cout << "ID: ";
            cin >> id;
            cin.ignore();

            cout << "Title: ";
            getline(cin, title);

            cout << "Author: ";
            getline(cin, author);

            lib.addBook(id, title, author);
            break;

        case 2:
            lib.displayBooks();
            break;

        case 3:
            cout << "Enter ID: ";
            cin >> id;

            lib.searchBook(id);
            break;

        case 4:
            cout << "Book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Student Name: ";
            getline(cin, student);

            lib.borrowBook(id, student);
            break;

        case 5:
            cout << "Book ID: ";
            cin >> id;

            lib.returnBook(id);
            break;

        case 6:
            cout << "Book ID: ";
            cin >> id;

            lib.showWaitlist(id);
            break;

        case 7:
            lib.transactions();
            break;

        case 8:
            cout << "Goodbye\n";
            break;

        default:
            cout << "Invalid choice\n";
        }

    } while (ch != 8);

    return 0;
}
