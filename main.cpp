#include <iostream>
#include "Account.h"
#include "Transaction.h"

int main() {
    try {
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

        std::cout << "Current Balance: " << newAccount.CalculateBalance() << std::endl;
    } catch (const std::exception& e) {
        throw std::runtime_error(std::string("Error: ") + e.what());
    }

    return 0;
}
