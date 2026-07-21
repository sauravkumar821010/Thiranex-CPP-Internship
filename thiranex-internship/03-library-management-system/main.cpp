/*
    Library Management System
    ---------------------------
    A console based C++ application to manage books, members and
    borrowing records using structured programming and file handling.

    Features:
        - Add a book / add a member
        - Issue a book to a member
        - Return a book
        - Search books by title or author
        - Display all books / all members
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

const char* BOOKS_FILE   = "books.dat";
const char* MEMBERS_FILE = "members.dat";

struct Book {
    int bookId;
    char title[100];
    char author[60];
    bool isIssued;
    int issuedToId;   // member id the book is currently issued to (-1 if none)
};

struct Member {
    int memberId;
    char name[50];
    char contact[15];
};

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

// ---------------- Book helpers ----------------

bool bookExists(int id) {
    ifstream file(BOOKS_FILE, ios::binary);
    if (!file) return false;

    Book b;
    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        if (b.bookId == id) return true;
    }
    return false;
}

void addBook() {
    Book b;
    cout << "\n--- Add New Book ---\n";
    cout << "Enter Book ID: ";
    cin >> b.bookId;
    clearInputBuffer();

    if (bookExists(b.bookId)) {
        cout << "A book with this ID already exists.\n";
        return;
    }

    cout << "Enter Title: ";
    cin.getline(b.title, 100);

    cout << "Enter Author: ";
    cin.getline(b.author, 60);

    b.isIssued = false;
    b.issuedToId = -1;

    ofstream file(BOOKS_FILE, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&b), sizeof(Book));
    file.close();

    cout << "Book added successfully!\n";
}

void printBookHeader() {
    cout << left
         << setw(8)  << "ID"
         << setw(35) << "Title"
         << setw(25) << "Author"
         << setw(10) << "Status" << "\n";
    cout << string(78, '-') << "\n";
}

void printBook(const Book& b) {
    cout << left
         << setw(8)  << b.bookId
         << setw(35) << b.title
         << setw(25) << b.author
         << setw(10) << (b.isIssued ? "Issued" : "Available") << "\n";
}

void displayAllBooks() {
    ifstream file(BOOKS_FILE, ios::binary);
    if (!file) {
        cout << "\nNo books found.\n";
        return;
    }

    Book b;
    bool found = false;

    cout << "\n--- All Books ---\n";
    printBookHeader();

    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        printBook(b);
        found = true;
    }

    if (!found) cout << "No books found.\n";
}

void searchBook() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    char keyword[100];

    cout << "\nEnter title or author keyword to search: ";
    cin.getline(keyword, 100);

    ifstream file(BOOKS_FILE, ios::binary);
    if (!file) {
        cout << "No books found.\n";
        return;
    }

    Book b;
    bool found = false;

    cout << "\n--- Search Results ---\n";
    printBookHeader();

    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        // simple case-sensitive substring search in title or author
        if (strstr(b.title, keyword) != nullptr || strstr(b.author, keyword) != nullptr) {
            printBook(b);
            found = true;
        }
    }

    if (!found) cout << "No matching books found.\n";
}

// ---------------- Member helpers ----------------

bool memberExists(int id) {
    ifstream file(MEMBERS_FILE, ios::binary);
    if (!file) return false;

    Member m;
    while (file.read(reinterpret_cast<char*>(&m), sizeof(Member))) {
        if (m.memberId == id) return true;
    }
    return false;
}

void addMember() {
    Member m;
    cout << "\n--- Add New Member ---\n";
    cout << "Enter Member ID: ";
    cin >> m.memberId;
    clearInputBuffer();

    if (memberExists(m.memberId)) {
        cout << "A member with this ID already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    cin.getline(m.name, 50);

    cout << "Enter Contact Number: ";
    cin.getline(m.contact, 15);

    ofstream file(MEMBERS_FILE, ios::binary | ios::app);
    file.write(reinterpret_cast<char*>(&m), sizeof(Member));
    file.close();

    cout << "Member added successfully!\n";
}

void displayAllMembers() {
    ifstream file(MEMBERS_FILE, ios::binary);
    if (!file) {
        cout << "\nNo members found.\n";
        return;
    }

    Member m;
    bool found = false;

    cout << "\n--- All Members ---\n";
    cout << left << setw(10) << "ID" << setw(25) << "Name" << setw(15) << "Contact" << "\n";
    cout << string(50, '-') << "\n";

    while (file.read(reinterpret_cast<char*>(&m), sizeof(Member))) {
        cout << left << setw(10) << m.memberId << setw(25) << m.name << setw(15) << m.contact << "\n";
        found = true;
    }

    if (!found) cout << "No members found.\n";
}

// ---------------- Issue / Return ----------------

void issueBook() {
    int bookId, memberId;

    cout << "\nEnter Book ID to issue: ";
    cin >> bookId;
    cout << "Enter Member ID: ";
    cin >> memberId;

    if (!memberExists(memberId)) {
        cout << "Member not found. Please add the member first.\n";
        return;
    }

    fstream file(BOOKS_FILE, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No books found.\n";
        return;
    }

    Book b;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        if (b.bookId == bookId) {
            found = true;

            if (b.isIssued) {
                cout << "This book is already issued.\n";
                return;
            }

            b.isIssued = true;
            b.issuedToId = memberId;

            int pos = -static_cast<int>(sizeof(Book));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&b), sizeof(Book));

            cout << "Book issued successfully to Member ID " << memberId << ".\n";
            break;
        }
    }

    if (!found) cout << "Book not found.\n";
}

void returnBook() {
    int bookId;
    cout << "\nEnter Book ID to return: ";
    cin >> bookId;

    fstream file(BOOKS_FILE, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No books found.\n";
        return;
    }

    Book b;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&b), sizeof(Book))) {
        if (b.bookId == bookId) {
            found = true;

            if (!b.isIssued) {
                cout << "This book was not issued.\n";
                return;
            }

            b.isIssued = false;
            b.issuedToId = -1;

            int pos = -static_cast<int>(sizeof(Book));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&b), sizeof(Book));

            cout << "Book returned successfully.\n";
            break;
        }
    }

    if (!found) cout << "Book not found.\n";
}

// ---------------- Menu ----------------

void showMenu() {
    cout << "\n============================================\n";
    cout << "         LIBRARY MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Add Book\n";
    cout << "2. Add Member\n";
    cout << "3. Issue Book\n";
    cout << "4. Return Book\n";
    cout << "5. Search Book (title/author)\n";
    cout << "6. Display All Books\n";
    cout << "7. Display All Members\n";
    cout << "8. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: addMember(); break;
            case 3: issueBook(); break;
            case 4: returnBook(); break;
            case 5: searchBook(); break;
            case 6: displayAllBooks(); break;
            case 7: displayAllMembers(); break;
            case 8: cout << "\nExiting... Thank you!\n"; break;
            default: cout << "Invalid choice, please try again.\n";
        }

        if (choice != 8) pause();

    } while (choice != 8);

    return 0;
}
