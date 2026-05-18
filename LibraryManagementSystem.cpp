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

// ================= LIBRARY =================
class Library {
    List list;
    Tree tree;

public:
    void addBook(int id, string title) {

        if (tree.search(id)) {
            cout << "Book already exists\n";
            return;
        }

        DLL* node = list.add(id, title);
        tree.insert(id, node);

        cout << "Book added\n";
    }

    void displayBooks() {
        DLL* cur = list.getHead();

        while (cur) {
            cout << cur->book.id
                 << " - "
                 << cur->book.title
                 << " ("
                 << (cur->book.available ? "Available" : "Borrowed")
                 << ")\n";

            cur = cur->next;
        }
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

            cout << "Book borrowed\n";
        }
        else {
            node->book.waitlist.enqueue(student);
            cout << "Added to waitlist\n";
        }
    }

    void returnBook(int id) {
        DLL* node = tree.search(id);

        if (!node) {
            cout << "Book not found\n";
            return;
        }

        if (node->book.waitlist.empty()) {
            node->book.available = true;
            node->book.borrower = "";
        }
        else {
            node->book.borrower = node->book.waitlist.dequeue();
            cout << "Book given to next student: "
                 << node->book.borrower << endl;
        }

        cout << "Book returned\n";
    }

    void searchBook(int id) {
        DLL* node = tree.search(id);

        if (!node)
            cout << "Book not found\n";
        else
            cout << node->book.title << endl;
    }
};

// ================= MAIN =================
int main() {

    Library lib;

    lib.addBook(101, "Clean Code");
    lib.addBook(102, "Data Structures");

    int ch, id;
    string title, student;

    do {
        cout << "\n1.Add Book\n";
        cout << "2.Display Books\n";
        cout << "3.Search Book\n";
        cout << "4.Borrow Book\n";
      