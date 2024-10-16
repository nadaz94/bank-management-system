#include <iostream>
#include <string>

using namespace std;

class Account {
public:
    int accountNumber;
    string accountHolderName;
    double balance;
    Account* next;

    Account(int accNum, string name) {
        accountNumber = accNum;
        accountHolderName = name;
        balance = 0.0;
        next = nullptr;
    }
};

class Bank {
private:
    Account* head;

public:
    Bank() : head(nullptr) {}

    void createAccount(int accNum, string name) {
        Account* newAccount = new Account(accNum, name);
        newAccount->next = head;
        head = newAccount;
        cout << "Account created for " << name << " with account number " << accNum << endl;
    }

    void deleteAccount(int accNum) {
        Account* current = head;
        Account* previous = nullptr;

        while (current != nullptr && current->accountNumber != accNum) {
            previous = current;
            current = current->next;
        }

        if (current == nullptr) {
            cout << "Account not found!" << endl;
            return;
        }

        if (previous == nullptr) {
            head = current->next;  // Deleting head
        }
        else {
            previous->next = current->next;
        }

        delete current;
        cout << "Account number " << accNum << " deleted successfully." << endl;
    }

    void deposit(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account) {
            account->balance += amount;
            cout << "Deposited: " << amount << " to account number " << accNum << endl;
        }
        else {
            cout << "Account not found!" << endl;
        }
    }

    void withdraw(int accNum, double amount) {
        Account* account = findAccount(accNum);
        if (account) {
            if (amount > account->balance) {
                cout << "Insufficient balance!" << endl;
            }
            else {
                account->balance -= amount;
                cout << "Withdrawn: " << amount << " from account number " << accNum << endl;
            }
        }
        else {
            cout << "Account not found!" << endl;
        }
    }

    void checkBalance(int accNum) {
        Account* account = findAccount(accNum);
        if (account) {
            cout << "Account number: " << accNum << ", Balance: " << account->balance << endl;
        }
        else {
            cout << "Account not found!" << endl;
        }
    }

    Account* findAccount(int accNum) {
        Account* current = head;
        while (current != nullptr) {
            if (current->accountNumber == accNum) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    ~Bank() {
        Account* current = head;
        while (current != nullptr) {
            Account* nextAccount = current->next;
            delete current;
            current = nextAccount;
        }
    }
};

int main() {
    Bank bank;
    int choice, accNum;
    string name;
    double amount;

    do {
        cout << "\nMenu:\n";
        cout << "1 - Create account\n";
        cout << "2 - Delete account\n";
        cout << "3 - Deposit\n";
        cout << "4 - Withdraw\n";
        cout << "5 - Check account balance\n";
        cout << "0 - Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter account number: ";
            cin >> accNum;
            cout << "Enter account holder name: ";
            cin >> name;
            bank.createAccount(accNum, name);
            break;
        case 2:
            cout << "Enter account number to delete: ";
            cin >> accNum;
            bank.deleteAccount(accNum);
            break;
        case 3:
            cout << "Enter account number to deposit: ";
            cin >> accNum;
            cout << "Enter amount to deposit: ";
            cin >> amount;
            bank.deposit(accNum, amount);
            break;
        case 4:
            cout << "Enter account number to withdraw: ";
            cin >> accNum;
            cout << "Enter amount to withdraw: ";
            cin >> amount;
            bank.withdraw(accNum, amount);
            break;
        case 5:
            cout << "Enter account number to check balance: ";
            cin >> accNum;
            bank.checkBalance(accNum);
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 0);

    return 0;
}