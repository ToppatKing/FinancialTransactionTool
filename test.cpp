#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "Account.h"
#include "Transaction.h"

TEST_CASE("CreateTransaction", "[Transaction]") {
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    REQUIRE(t.getName() == "Salary");
    REQUIRE(t.getAmount() == 1000.0);
    REQUIRE(t.getType() == Transaction::INCOME);
    REQUIRE(t.getDate() == now);
}

TEST_CASE("AddTransaction", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);
    auto transactions = account.searchTransactions("Salary", Transaction::INCOME, 1000.0, now);
    REQUIRE(transactions.size() == 1);
    REQUIRE(transactions[0].getName() == "Salary");
}

TEST_CASE("DeleteTransaction", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t1("Salary", 1000.0, Transaction::INCOME, now);
    Transaction t2("Rent", 500.0, Transaction::EXPENSE, now);
    account.addTransaction(t1);
    account.addTransaction(t2);
    REQUIRE(account.deleteTransaction("Rent"));
    auto transactions = account.searchTransactions("Rent", Transaction::EXPENSE, 500.0, now);
    REQUIRE(transactions.size() == 0);
    REQUIRE(account.CalculateBalance() == 1000.0);

    // Test per transazione non trovata
    REQUIRE_FALSE(account.deleteTransaction("NonExistent"));
}

TEST_CASE("ModifyTransaction", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);
    Transaction newTransaction("Salary", 1200.0, Transaction::INCOME, now);
    REQUIRE(account.modifyTransaction("Salary", newTransaction));
    auto transactions = account.searchTransactions("Salary", Transaction::INCOME, 1200.0, now);
    REQUIRE(transactions.size() == 1);
    REQUIRE(transactions[0].getAmount() == 1200.0);
    REQUIRE(account.CalculateBalance() == 1200.0);

    // Test per transazione non trovata
    Transaction nonExistentTransaction("NonExistent", 500.0, Transaction::EXPENSE, now);
    REQUIRE_FALSE(account.modifyTransaction("NonExistent", nonExistentTransaction));
}

TEST_CASE("SearchTransactions", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t1("Salary", 1000.0, Transaction::INCOME, now);
    Transaction t2("Rent", 500.0, Transaction::EXPENSE, now);
    account.addTransaction(t1);
    account.addTransaction(t2);
    auto transactions = account.searchTransactions("", Transaction::INCOME, 0, 0);
    REQUIRE(transactions.size() == 1);
    REQUIRE(transactions[0].getName() == "Salary");
}

TEST_CASE("SaveToFile", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);
    account.saveToFile("test_transactions.txt");

    // Verifica che il file esista
    std::ifstream file("test_transactions.txt");
    REQUIRE(file.good());
}

TEST_CASE("LoadFromFile", "[Account]") {
    // Crea un account e aggiungi una transazione
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);

    // Salva le transazioni su file
    account.saveToFile("test_transactions.txt");

    // Crea un nuovo account e carica le transazioni dal file
    Account newAccount("MyAccount", 0.0);
    try {
        newAccount.loadFromFile("test_transactions.txt");

        // Cerca la transazione caricata
        auto transactions = newAccount.searchTransactions("Salary", Transaction::INCOME, 1000.0, now);
        REQUIRE(transactions.size() == 1);
        REQUIRE(transactions[0].getName() == "Salary");

        // Debug: stampa le transazioni caricate
        for (const auto& transaction : transactions) {
            std::cout << "Loaded Transaction: " << transaction.getName() << ", Amount: " << transaction.getAmount() << std::endl;
        }
    } catch (const std::runtime_error& e) {
        FAIL(e.what());
    }
}

TEST_CASE("CalculateBalance", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t1("Salary", 1000.0, Transaction::INCOME, now);
    Transaction t2("Rent", 500.0, Transaction::EXPENSE, now);
    account.addTransaction(t1);
    account.addTransaction(t2);
    REQUIRE(account.CalculateBalance() == 500.0);
}

TEST_CASE("InvalidTransactionAmount", "[Transaction]") {
    std::time_t now = std::time(nullptr);
    REQUIRE_THROWS_AS(Transaction("Invalid", -100.0, Transaction::EXPENSE, now), std::invalid_argument);
    REQUIRE_THROWS_AS(Transaction("Invalid", 0.0, Transaction::EXPENSE, now), std::invalid_argument);
}
