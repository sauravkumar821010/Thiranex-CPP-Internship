# Library Management System (C++)

A console-based Library Management System built in C++ for the Thiranex internship task. It manages books, members, and issue/return records using structured data and file handling.

## What it does

- Add a book (ID, title, author)
- Add a member (ID, name, contact number)
- Issue a book to a registered member
- Return an issued book
- Search books by title or author (keyword search)
- Display all books, with their issued/available status
- Display all registered members

## Design notes

Books and members are stored in two separate binary files, `books.dat` and `members.dat`, using `struct Book` and `struct Member`. Each `Book` record keeps track of whether it's currently issued and, if so, which member ID it's issued to.

- A book can't be issued if it's already marked as issued, and it can't be issued to a member ID that doesn't exist in `members.dat`.
- Issuing/returning updates the book's record in place using `seekp()`, instead of rewriting the whole file.
- Search uses a simple substring match (`strstr`) against the title and author fields, so partial keywords work (e.g. searching "Alchemist" matches "The Alchemist").

## Files

```
03-library-management-system/
├── main.cpp
├── Makefile
└── README.md
```

## How to run

```bash
g++ -std=c++17 -Wall -o library main.cpp
./library
```

or:

```bash
make run
```

`books.dat` and `members.dat` are created automatically as soon as you add a book or member.

## Sample menu

```
============================================
         LIBRARY MANAGEMENT SYSTEM
============================================
1. Add Book
2. Add Member
3. Issue Book
4. Return Book
5. Search Book (title/author)
6. Display All Books
7. Display All Members
8. Exit
============================================
Enter your choice:
```

## Possible improvements

- Due dates and late-return fines
- Limiting how many books a member can issue at once
- Case-insensitive search
