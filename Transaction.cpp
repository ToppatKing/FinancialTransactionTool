#include "Transaction.h"

Transaction::Transaction(const std::string& name, double amount, Type type, const std::time_t& date)
        : name(name), amount(amount), type(type), date(date) {}

std::string Transaction::getName() const { return name; }
double Transaction::getAmount() const { return amount; }
Transaction::Type Transaction::getType() const { return type; }
std::time_t Transaction::getDate() const { return date; }

void Transaction::setName(const std::string& newName) { name = newName; }
void Transaction::setAmount(double newAmount) { amount = newAmount; }
void Transaction::setType(Type newType) { type = newType; }
void Transaction::setDate(const std::time_t& newDate) { date = newDate; }

std::string Transaction::typeToString(Type type) {
    switch (type) {
        case INCOME: return "INCOME";
        case EXPENSE: return "EXPENSE";
        default: return "UNKNOWN";
    }
}

Transaction::Type Transaction::stringToType(const std::string& typeStr) {
    if (typeStr == "INCOME") return INCOME;
    if (typeStr == "EXPENSE") return EXPENSE;
    return UNKNOWN;
}
