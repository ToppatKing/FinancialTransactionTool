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
