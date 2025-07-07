#include <iostream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;


class Transaction {
    string type;
    double amount;
    string timeStamp;

public:
    Transaction(string type, double amount) {
        this->type = type;
        this->amount = amount;


        time_t now = time(0);
        timeStamp = ctime(&now);
        timeStamp.pop_back();
    }

    void display() {
        cout << "Type: " << type << ", Amount: " << amount << ", Time: " << timeStamp << endl;
    }
};


class Account {
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string accNum, double initialBalance = 0.0) {
        accountNumber = accNum;
        balance = initialBalance;
    }

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        balance += amount;
        transactions.push_back(Transaction("Deposit", amount));
        cout << "Deposit Successful.\n";
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient Balance!\n";
            return false;
        }
        balance -= amount;
        transactions.push_back(Transaction("Withdrawal", amount));
        cout << "Withdrawal Successful.\n";
        return true;
    }

    bool transfer(Account &to, double amount) {
        if (withdraw(amount)) {
            to.deposit(amount);
            transactions.push_back(Transaction("Transfer to " + to.getAccountNumber(), amount));
            return true;
        }
        return false;
    }

    void showTransactions() {
        cout << "Transaction History for Account " << accountNumber << ":\n";
        for (auto &t : transactions) {
            t.display();
        }
    }

    void showAccountInfo() {
        cout << "\nAccount Number: " << accountNumber << "\nBalance: " << balance << "\n";
        showTransactions();
    }
};

// Customer class
class Customer {
    string name;
    string customerId;
    Account account;

public:
    Customer(string name, string id, string accNum, double initialDeposit = 0.0)
        : account(accNum, initialDeposit) {
        this->name = name;
        customerId = id;
    }

    Account& getAccount() {
        return account;
    }

    void showCustomerInfo() {
        cout << "\nCustomer Name: " << name << "\nCustomer ID: " << customerId;
        account.showAccountInfo();
    }
};


int main() {
    Customer c1("Raunak Singh", "C101", "ACC001", 1000);
    Customer c2("Aryan Kumar", "C102", "ACC002", 500);

    c1.getAccount().deposit(200);
    c1.getAccount().withdraw(150);
    c1.getAccount().transfer(c2.getAccount(), 300);

    c1.showCustomerInfo();
    c2.showCustomerInfo();

    return 0;
}
