#define CATCH_CONFIG_MAIN
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
    account.deleteTransaction("Rent");
    auto transactions = account.searchTransactions("Rent", Transaction::EXPENSE, 500.0, now);
    REQUIRE(transactions.size() == 0);
}

TEST_CASE("ModifyTransaction", "[Account]") {
    Account account("MyAccount", 0.0);
    std::time_t now = std::time(nullptr);
    Transaction t("Salary", 1000.0, Transaction::INCOME, now);
    account.addTransaction(t);
    Transaction newTransaction("Salary", 1200.0, Transaction::INCOME, now);
    account.modifyTransaction("Salary", newTransaction);
    auto transactions = account.searchTransactions("Salary", Transaction::INCOME, 1200.0, now);
    REQUIRE(transactions.size() == 1);
    REQUIRE(transactions[0].getAmount() == 1200.0);
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
    Account account("MyAccount", 0.0);
    account.loadFromFile("test_transactions.txt");
    auto transactions = account.searchTransactions("Salary", Transaction::INCOME, 1000.0, 0);
    REQUIRE(transactions.size() == 1);
    REQUIRE(transactions[0].getName() == "Salary");
}
