# Bank Management Application (C++)

A console-based Bank Management Application built in C++ for the Thiranex internship task. It simulates core banking operations using OOP concepts and file handling so account data persists between runs.

## What it does

- Open a new account (account number, holder name, account type, initial deposit)
- Deposit money
- Withdraw money (blocks the transaction if funds are insufficient)
- Check balance
- View all accounts
- Close an account

Every deposit/withdrawal prints a small transaction receipt with the updated balance.

## Design notes

The `Account` class encapsulates account data (account number, name, type, balance) and exposes `deposit()` and `withdraw()` methods rather than letting outside code touch the balance directly. Accounts are stored as binary records in `accounts.dat`, and updates (deposit/withdraw) are done in-place by seeking to the record's position, rather than rewriting the whole file. Closing an account rebuilds the file without that record.

Withdrawals are validated against the current balance — you can't overdraw an account.

## Files

```
02-bank-management-application/
├── main.cpp
├── Makefile
└── README.md
```

## How to run

```bash
g++ -std=c++17 -Wall -o bank main.cpp
./bank
```

or:

```bash
make run
```

`accounts.dat` is created automatically the first time you open an account.

## Sample menu

```
============================================
         BANK MANAGEMENT APPLICATION
============================================
1. Open New Account
2. Deposit Money
3. Withdraw Money
4. Check Balance
5. View All Accounts
6. Close Account
7. Exit
============================================
Enter your choice:
```

## Possible improvements

- Transaction history log per account
- Interest calculation for savings accounts
- PIN/password protection for withdrawals
