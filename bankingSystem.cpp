#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>

using namespace std;

// --- Transaction Class ---
class Transaction {
public:
    string type;
    double amount;
    string date;

    Transaction(string t, double a) : type(t), amount(a) {
        time_t now = time(0);
        date = ctime(&now);
        date.pop_back(); // Remove newline character from ctime
    }
};

// --- Account Class ---
class Account {
private:
    int accountNumber;
    double balance;
    vector<Transaction> history;

public:
    Account(int accNum, double initialDeposit) : accountNumber(accNum), balance(initialDeposit) {
        if (initialDeposit > 0) {
            history.push_back(Transaction("Initial Deposit", initialDeposit));
        }
    }

    void deposit(double amount) {
        balance += amount;
        history.push_back(Transaction("Deposit", amount));
    }

    bool withdraw(double amount) {
        if (amount > balance) return false;
        balance -= amount;
        history.push_back(Transaction("Withdrawal", amount));
        return true;
    }

    int getAccountNumber() const { return accountNumber; }
    double getBalance() const { return balance; }
    
    void showHistory() const {
        cout << "\n--- History for Acc #" << accountNumber << " ---\n";
        for (const auto& t : history) {
            cout << "[" << t.date << "] " << left << setw(15) << t.type 
                 << ": $" << fixed << setprecision(2) << t.amount << endl;
        }
    }
};

// --- Customer Class ---
class Customer {
public:
    string name;
    int customerID;
    vector<Account*> accounts;

    Customer(string n, int id) : name(n), customerID(id) {}

    void addAccount(Account* acc) {
        accounts.push_back(acc);
    }
};

// --- Bank Controller Class ---
class Bank {
private:
    vector<Customer*> customers;
    vector<Account*> allAccounts;
    int nextAccNum = 1001;

public:
    void createCustomer(string name, int id) {
        customers.push_back(new Customer(name, id));
    }

    void openAccount(int customerID, double initialDeposit) {
        for (auto c : customers) {
            if (c->customerID == customerID) {
                Account* newAcc = new Account(nextAccNum++, initialDeposit);
                c->addAccount(newAcc);
                allAccounts.push_back(newAcc);
                cout << "Account created! Number: " << newAcc->getAccountNumber() << endl;
                return;
            }
        }
        cout << "Customer ID not found.\n";
    }

    Account* findAccount(int accNum) {
        for (auto a : allAccounts) {
            if (a->getAccountNumber() == accNum) return a;
        }
        return nullptr;
    }

    void transfer(int fromAcc, int toAcc, double amount) {
        Account* src = findAccount(fromAcc);
        Account* dest = findAccount(toAcc);

        if (src && dest && src->withdraw(amount)) {
            dest->deposit(amount);
            cout << "Transfer Successful!\n";
        } else {
            cout << "Transfer Failed (Invalid accounts or insufficient funds).\n";
        }
    }
};

int main() {
    Bank myBank;
    myBank.createCustomer("Alice Smith", 1);
    myBank.openAccount(1, 500.00); 
    myBank.openAccount(1, 200.00); 

 
    Account* acc1 = myBank.findAccount(1001);
    Account* acc2 = myBank.findAccount(1002);

    acc1->deposit(150.0);
    myBank.transfer(1001, 1002, 100.0);

    cout << "\nFinal Balances:";
    cout << "\nAcc 1001: $" << acc1->getBalance();
    cout << "\nAcc 1002: $" << acc2->getBalance() << endl;

    acc1->showHistory();
    acc2->showHistory();

    return 0;
}