#include "Account.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <stdexcept>

Account::Account(const std::string& name, double initialBalance)
        : name(name), balance(initialBalance) {}

void Account::addTransaction(const Transaction& transaction) {
    transactions.push_back(transaction);
    updateBalance(transaction, true);
}

bool Account::deleteTransaction(const std::string& transactionName) {
    for (auto it = transactions.begin(); it != transactions.end(); ++it) {
        if (it->getName() == transactionName) {
            updateBalance(*it, false);
            transactions.erase(it);
            return true;
        }
    }
    return false;
}

bool Account::modifyTransaction(const std::string& transactionName, const Transaction& newTransaction) {
    for (auto& transaction : transactions) {
        if (transaction.getName() == transactionName) {
            updateBalance(transaction, false);
            transaction = newTransaction;
            updateBalance(newTransaction, true);
            return true;
        }
    }
    return false;
}

std::vector<Transaction> Account::searchTransactions(const std::string& name, Transaction::Type type, double amount, const std::time_t& date) {
    std::vector<Transaction> results;
    for (const auto& transaction : transactions) {
        if ((name.empty() || transaction.getName() == name) &&
            (type == Transaction::UNKNOWN || transaction.getType() == type) &&
            (amount == 0 || transaction.getAmount() == amount) &&
            (date == 0 || transaction.getDate() == date)) {
            results.push_back(transaction);
        }
    }
    return results;
}

void Account::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (const auto& transaction : transactions) {
        file << transaction.getName() << "," << transaction.getAmount() << ","
             << Transaction::typeToString(transaction.getType()) << "," << transaction.getDate() << "\n";
    }
}

void Account::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name, typeStr;
        double amount;
        std::time_t date;
        char delimiter;

        if (std::getline(iss, name, ',') && iss >> amount >> delimiter && std::getline(iss, typeStr, ',') && iss >> date) {
            Transaction::Type type = Transaction::stringToType(typeStr);
            transactions.emplace_back(name, amount, type, date);
        } else {
            throw std::runtime_error("Error reading line: " + line);
        }
    }
}

double Account::CalculateBalance() const {
    return balance;
}

void Account::updateBalance(const Transaction& transaction, bool isAdding) {
    if (isAdding) {
        if (transaction.getType() == Transaction::INCOME) {
            balance += transaction.getAmount();
        } else if (transaction.getType() == Transaction::EXPENSE) {
            balance -= transaction.getAmount();
        }
    } else {
        if (transaction.getType() == Transaction::INCOME) {
            balance -= transaction.getAmount();
        } else if (transaction.getType() == Transaction::EXPENSE) {
            balance += transaction.getAmount();
        }
    }
}
