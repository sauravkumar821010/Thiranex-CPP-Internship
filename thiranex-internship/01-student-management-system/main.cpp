/*
    Student Management System
    --------------------------
    A console based application to manage student records.
    Records are stored in a binary file (students.dat) so that
    data stays persistent between runs.

    Features:
        - Add student
        - View all students
        - Search student by ID
        - Update student
        - Delete student
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

const char* FILE_NAME = "students.dat";

struct Student {
    int id;
    char name[50];
    int age;
    char course[30];
    char contact[15];
};

// clears any leftover input in the stream (used after cin >> to avoid getline issues)
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

bool studentExists(int id) {
    ifstream file(FILE_NAME, ios::binary);
    if (!file) return false;

    Student temp;
    while (file.read(reinterpret_cast<char*>(&temp), sizeof(Student))) {
        if (temp.id == id) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void addStudent() {
    Student s;

    cout << "\n--- Add New Student ---\n";
    cout << "Enter Student ID: ";
    cin >> s.id;
    clearInputBuffer();

    if (studentExists(s.id)) {
        cout << "A student with this ID already exists.\n";
        return;
    }

    cout << "Enter Name: ";
    cin.getline(s.name, 50);

    cout << "Enter Age: ";
    cin >> s.age;
    clearInputBuffer();

    cout << "Enter Course: ";
    cin.getline(s.course, 30);

    cout << "Enter Contact Number: ";
    cin.getline(s.contact, 15);

    ofstream file(FILE_NAME, ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    file.write(reinterpret_cast<char*>(&s), sizeof(Student));
    file.close();

    cout << "Student record added successfully!\n";
}

void printHeader() {
    cout << left
         << setw(8)  << "ID"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(15) << "Course"
         << setw(15) << "Contact" << "\n";
    cout << string(64, '-') << "\n";
}

void printStudent(const Student& s) {
    cout << left
         << setw(8)  << s.id
         << setw(20) << s.name
         << setw(6)  << s.age
         << setw(15) << s.course
         << setw(15) << s.contact << "\n";
}

void viewAllStudents() {
    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "\nNo records found.\n";
        return;
    }

    Student s;
    bool found = false;

    cout << "\n--- Student Records ---\n";
    printHeader();

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        printStudent(s);
        found = true;
    }
    file.close();

    if (!found) cout << "No records found.\n";
}

void searchStudent() {
    int id;
    cout << "\nEnter Student ID to search: ";
    cin >> id;
    clearInputBuffer();

    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            cout << "\nStudent Found:\n";
            printHeader();
            printStudent(s);
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << "No student found with ID " << id << ".\n";
}

void updateStudent() {
    int id;
    cout << "\nEnter Student ID to update: ";
    cin >> id;
    clearInputBuffer();

    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            found = true;

            cout << "Enter new Name: ";
            cin.getline(s.name, 50);

            cout << "Enter new Age: ";
            cin >> s.age;
            clearInputBuffer();

            cout << "Enter new Course: ";
            cin.getline(s.course, 30);

            cout << "Enter new Contact Number: ";
            cin.getline(s.contact, 15);

            // move the file pointer back to the start of this record and overwrite it
            int pos = -static_cast<int>(sizeof(Student));
            file.seekp(pos, ios::cur);
            file.write(reinterpret_cast<char*>(&s), sizeof(Student));
            cout << "Record updated successfully!\n";
            break;
        }
    }
    file.close();

    if (!found) cout << "No student found with ID " << id << ".\n";
}

void deleteStudent() {
    int id;
    cout << "\nEnter Student ID to delete: ";
    cin >> id;
    clearInputBuffer();

    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No records found.\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);
    Student s;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        if (s.id == id) {
            found = true;
            continue; // skip writing this record, effectively deleting it
        }
        temp.write(reinterpret_cast<char*>(&s), sizeof(Student));
    }

    file.close();
    temp.close();

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) cout << "Student record deleted successfully!\n";
    else cout << "No student found with ID " << id << ".\n";
}

void showMenu() {
    cout << "\n============================================\n";
    cout << "         STUDENT MANAGEMENT SYSTEM\n";
    cout << "============================================\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;
        clearInputBuffer();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "\nExiting... Thank you!\n"; break;
            default: cout << "Invalid choice, please try again.\n";
        }

        if (choice != 6) pause();

    } while (choice != 6);

    return 0;
}
