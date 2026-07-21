# Thiranex Internship – C++ Console Projects

This repo contains my submissions for the Thiranex internship tasks. All three are console-based C++ applications that use file handling to persist data between runs.

| # | Project | Folder |
|---|---------|--------|
| 1 | Student Management System | [`01-student-management-system`](./01-student-management-system) |
| 2 | Bank Management Application | [`02-bank-management-application`](./02-bank-management-application) |
| 3 | Library Management System | [`03-library-management-system`](./03-library-management-system) |

Each folder is a self-contained project with its own `main.cpp`, `Makefile`, and `README.md` explaining what it does and how to run it.

## Tech used

- C++17
- Standard library file I/O (`fstream`) — no external dependencies
- g++ / Makefiles for building

## How to build any of them

```bash
cd 01-student-management-system   # or 02-... / 03-...
g++ -std=c++17 -Wall -o app main.cpp
./app
```

Each program is menu-driven — just run it and follow the on-screen options.

## Notes

- Data files (`*.dat`) are generated automatically the first time you add a record, and are excluded from this repo via `.gitignore` since they're runtime output, not source.
- All three were compiled and manually tested end-to-end (add/view/search/update/delete-style flows for each) before submission.
