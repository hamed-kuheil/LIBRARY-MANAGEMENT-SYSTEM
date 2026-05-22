#include <iostream>
#include <string>
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

    void enqueue(string n) {
        QNode* temp = new QNode(n);

        if (!rear)
            front = rear = temp;
        else {
            rear->next = temp;
            rear = temp;
        }
    }

    string dequeue() {
        if (!front)
            return "";

        QNode* temp = front;
        string n = temp->name;

        front = front->next;

        if (!front)
            rear = nullptr;

        delete temp;
        return n;
    }

    bool empty() {
        return front == nullptr;
    }

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }
};

// ================= BOOK =================
class Book {
public:
    int id;
    string title;
    bool available;
    string borrower;
    Queue waitlist;

    Book(int i = 0, string t = "") {
        id = i;
        title = t;
        available = true;
        borrower = "";
    }
};

// ================= DOUBLY LINKED LIST =================
struct DLL {
    Book book;
    DLL *next, *prev;

    DLL(int id, string title)
        : book(id, title) {

        next = prev = nullptr;
    }
};

class List {
    DLL *head, *tail;

public:
    List() {
        head = tail = nullptr;
    }

    DLL* add(int id, string title) {
        DLL* temp = new DLL(id, title);

        if (!head)
            head = tail = temp;
        else {
            tail->next = temp;
            temp->prev = tail;
            tail = temp;
        }

        return temp;
    }

    DLL* getHead() {
        return head;
    }

    ~List() {
        DLL* cur = head;

        while (cur) {
            DLL* temp = cur;
            cur = cur->next;
            delete temp;
        }
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

    void destroy(BST* node) {
        if (!node)
            return;

        destroy(node->left);
        destroy(node->right);

        delete node;
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

    ~Tree() {
        destroy(root);
    }
};

// ================= LIBRARY =================
class Library {
    List list;
    Tree tree;

    // Admin Data
    string adminName = "admin";
    string adminPassword = "admin1234";

    bool adminLogin() {

        string username, password;

        cout << "\n===== ADMIN LOGIN =====\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);

        if (username == adminName &&
            password == adminPassword) {

            cout << "Login Successful\n";
            return true;
        }

        cout << "Wrong Username or Password\n";
        return false;
    }

public:

    void addBook(int id, string title) {

        // Admin Authentication
        if (!adminLogin())
            return;

        if (tree.search(id)) {
            cout << "Book already exists\n";
            return;
        }

        DLL* node = list.add(id, title);
        tree.insert(id, node);

        cout << "Book added successfully\n";
    }

    void displayBooks() {

        DLL* cur = list.getHead();

        if (!cur) {
            cout << "No books in library\n";
            return;
        }

        cout << "\n===== BOOKS =====\n";

        while (cur) {

            cout << "ID: "
                 << cur->book.id << endl;

            cout << "Title: "
                 << cur->book.title << endl;

            cout << "Status: "
                 << (cur->book.available ?
                    "Available" : "Borrowed")
                 << endl;

            if (!cur->book.available) {

                cout << "Borrowed By: "
                     << cur->book.borrower
                     << endl;
            }

            cout << "---------------------\n";

            cur = cur->next;
        }
    }

    void searchBook(int id) {

        DLL* node = tree.search(id);

        if (!node) {
            cout << "Book not found\n";
            return;
        }

        cout << "\n===== BOOK FOUND =====\n";

        cout << "ID: "
             << node->book.id << endl;

        cout << "Title: "
             << node->book.title << endl;

        cout << "Status: "
             << (node->book.available ?
                "Available" : "Borrowed")
             << endl;
    }

    void borrowBook(int id, string student) {

        DLL* node = tree.search(id);

        if (!node) {
            cout << "Book not found\n";
            return;
        }

        if (node->book.available) {

            node->book.available = false;
            node->book.borrower = student;

            cout << "Book borrowed successfully\n";
        }
        else {

            node->book.waitlist.enqueue(student);

            cout << "Book unavailable -> Added to waitlist\n";
        }
    }

    void returnBook(int id) {

        DLL* node = tree.search(id);

        if (!node) {
            cout << "Book not found\n";
            return;
        }

        if (node->book.available) {
            cout << "Book already available\n";
            return;
        }

        if (node->book.waitlist.empty()) {

            node->book.available = true;
            node->book.borrower = "";

            cout << "Book returned successfully\n";
        }
        else {

            node->book.borrower =
                node->book.waitlist.dequeue();

            cout << "Book automatically given to: "
                 << node->book.borrower
                 << endl;
        }
    }
};

// ================= MAIN =================
int main() {

    Library lib;

    int ch, id;
    string title, student;

    do {

        cout << "\n========== LIBRARY SYSTEM ==========\n";

        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Borrow Book\n";
        cout << "5. Return Book\n";
        cout << "6. Exit\n";

        cout << "Enter Choice: ";

        cin >> ch;
        cin.ignore();

        switch (ch) {

        case 1:

            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Book Title: ";
            getline(cin, title);

            lib.addBook(id, title);

            break;

        case 2:

            lib.displayBooks();

            break;

        case 3:

            cout << "Enter Book ID: ";
            cin >> id;

            lib.searchBook(id);

            break;

        case 4:

            cout << "Enter Book ID: ";
            cin >> id;
            cin.ignore();

            cout << "Enter Student Name: ";
            getline(cin, student);

            lib.borrowBook(id, student);

            break;

        case 5:

            cout << "Enter Book ID: ";
            cin >> id;

            lib.returnBook(id);

            break;

        case 6:

            cout << "Exiting Program...\n";

            break;

        default:

            cout << "Invalid Choice\n";
        }

    } while (ch != 6);

    return 0;
}
