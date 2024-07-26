#include <iostream>
#include "Account.h"
#include "Transaction.h"

int main() {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);

    account.saveToFile("transactions.txt");

    Account newAccount("MyAccount", 0.0);
    newAccount.loadFromFile("transactions.txt");

    auto transactions = newAccount.searchTransactions("Salary", Transaction::INCOME, 1000.0, now);
    for (const auto& transaction : transactions) {
        std::cout << "Transaction: " << transaction.getName() << ", Amount: " << transaction.getAmount() << std::endl;
    }

    return 0;
}
