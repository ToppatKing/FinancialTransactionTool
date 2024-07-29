#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>
#include <vector>
#include "Transaction.h"

class Account {
public:
    Account(const std::string& name, double initialBalance);

    void addTransaction(const Transaction& transaction);
    bool deleteTransaction(const std::string& transactionName);
    bool modifyTransaction(const std::string& transactionName, const Transaction& newTransaction);
    std::vector<Transaction> searchTransactions(const std::string& name, Transaction::Type type, double amount, const std::time_t& date);
    void saveToFile(const std::string& filename);
    void loadFromFile(const std::string& filename);
    double CalculateBalance() const;

private:
    std::string name;
    double balance;
    std::vector<Transaction> transactions;

    void updateBalance(const Transaction& transaction, bool isAdding);
};

#endif // ACCOUNT_H
