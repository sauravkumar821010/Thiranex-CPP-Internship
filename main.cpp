# Student Management System (C++)

A console-based Student Management System built in C++ as part of the Thiranex internship task. It manages student records with persistent storage using file handling, so data isn't lost when the program closes.

## What it does

- Add a new student record (ID, name, age, course, contact number)
- View all student records in a table
- Search for a student by ID
- Update an existing student's details
- Delete a student record

## How it works

Student records are stored as fixed-size binary records in `students.dat`. Each record is a `struct Student`, which makes updating/deleting straightforward — the program can seek to the exact byte offset of a record and overwrite it in place, instead of rewriting the whole file every time (except for delete, where the file is rebuilt without the removed record).

The program checks for duplicate IDs before adding a new student, and validates that a student exists before letting you update or delete them.

## Files

```
01-student-management-system/
├── main.cpp      # all the source code
├── Makefile      # build helper
└── README.md
```

## How to run

```bash
g++ -std=c++17 -Wall -o sms main.cpp
./sms
```

or, if you have `make`:

```bash
make run
```

`students.dat` gets created automatically the first time you add a student — you don't need to create it yourself.

## Sample menu

```
============================================
         STUDENT MANAGEMENT SYSTEM
============================================
1. Add Student
2. View All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
============================================
Enter your choice:
```

## Possible improvements

- Sorting students by name/course
- Exporting records to CSV
- Basic input validation for age/contact format
