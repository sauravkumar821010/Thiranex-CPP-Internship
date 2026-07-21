/*
    Bank Management Application
    ----------------------------
    A console based C++ application that simulates core banking
    operations using object oriented programming and file handling.

    Features:
        - Open a new account
        - Deposit money
        - Withdraw money
        - Check balance
        - View all accounts
        - Close an account
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>

using namespace std;

const char* FILE_NAME = "accounts.dat";

class Account {
private:
    int accNo;
    char name[50];
    char accType[15]; // "Savings" or "Current"
    double balance;

public:
    void openAccount() {
        cout << "Enter Account Number: ";
        cin >> accNo;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Account Holder Name: ";
        cin.getline(name, 50);

        cout << "Enter Account Type (Savings/Current): ";
        cin.getline(accType, 15);

        cout << "Enter Initial Deposit Amount: ";
        cin >> balance;
        // note: leftover newline after this is cleared by the main menu loop
    }

    void deposit(double amount) { balance += amount; }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        return true;
    }

    int getAccNo() const { return accNo; }
    double getBalance() const { return balance; }

    void display() const {
        cout << left
             << setw(10) << accNo
             << setw(20) << name
             << setw(12) << accType
             << fixed << setprecision(2) << setw(12) << balance << "\n";
    }

    void printReceipt(const string& transactionType, double amount) const {
        cout << "\n------------------------------------\n";
        cout << "        TRANSACTION RECEIPT\n";
        cout << "------------------------------------\n";
        cout << "Account No : " << accNo << "\n";
        cout << "Name       : " << name << "\n";
        cout << "Transaction: " << transactionType << "\n";
        cout << "Amount     : " << fixed << setprecision(2) << amount << "\n";
        cout << "New Balance: " << fixed << setprecision(2) << balance << "\n";
        cout << "------------------------------------\n";
    }
};

void pause() {
    cout << "\nPress Enter to continue...";
    cin.get();
}

bool accountExists(int accNo) {
    ifstream file(FILE_NAME, ios::binary);
    if (!file) return false;

    Account acc;
    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

void createAccount() {
    Account acc;
    cout << "\n--- Open New Account ---\n";
    acc.openAccount();

    if (accountExists(acc.getAccNo())) {
        cout << "An account with this number already exists.\n";
        return;
    }

    ofstream file(FILE_NAME, ios::binary | ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }
    file.write(reinterpret_cast<char*>(&acc), sizeof(Account));
    file.close();

    cout << "Account created successfully!\n";
}

// finds account by number, returns true if found, and if updated
// also writes the updated record back to the file at the same position
bool modifyAccount(int accNo, double amount, const string& mode, Account& result) {
    fstream file(FILE_NAME, ios::binary | ios::in | ios::out);
    if (!file) return false;

    Account acc;
    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            bool success = true;

            if (mode == "deposit") {
                acc.deposit(amount);
            } else if (mode == "withdraw") {
                success = acc.withdraw(amount);
            }

            if (success) {
                int pos = -static_cast<int>(sizeof(Account));
                file.seekp(pos, ios::cur);
                file.write(reinterpret_cast<char*>(&acc), sizeof(Account));
            }

            result = acc;
            file.close();
            return success;
        }
    }
    file.close();
    return false;
}

void depositMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;
    cout << "Enter Deposit Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Deposit amount must be positive.\n";
        return;
    }

    Account acc;
    if (modifyAccount(accNo, amount, "deposit", acc)) {
        acc.printReceipt("Deposit", amount);
    } else {
        cout << "Account not found.\n";
    }
}

void withdrawMoney() {
    int accNo;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accNo;
    cout << "Enter Withdrawal Amount: ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Withdrawal amount must be positive.\n";
        return;
    }

    if (!accountExists(accNo)) {
        cout << "Account not found.\n";
        return;
    }

    Account acc;
    if (modifyAccount(accNo, amount, "withdraw", acc)) {
        acc.printReceipt("Withdrawal", amount);
    } else {
        cout << "Insufficient balance.\n";
    }
}

void checkBalance() {
    int accNo;
    cout << "\nEnter Account Number: ";
    cin >> accNo;

    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No accounts found.\n";
        return;
    }

    Account acc;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            cout << "\nCurrent Balance: Rs. " << fixed << setprecision(2)
                 << acc.getBalance() << "\n";
            found = true;
            break;
        }
    }
    file.close();

    if (!found) cout << "Account not found.\n";
}

void printHeader() {
    cout << left
         << setw(10) << "Acc No"
         << setw(20) << "Name"
         << setw(12) << "Type"
         << setw(12) << "Balance" << "\n";
    cout << string(54, '-') << "\n";
}

void viewAllAccounts() {
    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "\nNo accounts found.\n";
        return;
    }

    Account acc;
    bool found = false;

    cout << "\n--- All Accounts ---\n";
    printHeader();

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        acc.display();
        found = true;
    }
    file.close();

    if (!found) cout << "No accounts found.\n";
}

void closeAccount() {
    int accNo;
    cout << "\nEnter Account Number to close: ";
    cin >> accNo;

    ifstream file(FILE_NAME, ios::binary);
    if (!file) {
        cout << "No accounts found.\n";
        return;
    }

    ofstream temp("temp.dat", ios::binary);
    Account acc;
    bool found = false;

    while (file.read(reinterpret_cast<char*>(&acc), sizeof(Account))) {
        if (acc.getAccNo() == accNo) {
            found = true;
            continue;
        }
        temp.write(reinterpret_cast<char*>(&acc), sizeof(Account));
    }

    file.close();
    temp.close();

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found) cout << "Account closed successfully.\n";
    else cout << "Account not found.\n";
}

void showMenu() {
    cout << "\n============================================\n";
    cout << "         BANK MANAGEMENT APPLICATION\n";
    cout << "============================================\n";
    cout << "1. Open New Account\n";
    cout << "2. Deposit Money\n";
    cout << "3. Withdraw Money\n";
    cout << "4. Check Balance\n";
    cout << "5. View All Accounts\n";
    cout << "6. Close Account\n";
    cout << "7. Exit\n";
    cout << "============================================\n";
    cout << "Enter your choice: ";
}

int main() {
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: depositMoney(); break;
            case 3: withdrawMoney(); break;
            case 4: checkBalance(); break;
            case 5: viewAllAccounts(); break;
            case 6: closeAccount(); break;
            case 7: cout << "\nThank you for banking with us!\n"; break;
            default: cout << "Invalid choice, please try again.\n";
        }

        if (choice != 7) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pause();
        }

    } while (choice != 7);

    return 0;
}
