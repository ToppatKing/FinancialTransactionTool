#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <ctime>
#include <stdexcept>

class Transaction {
public:
    enum Type { INCOME, EXPENSE, UNKNOWN };

    Transaction(const std::string& name, double amount, Type type, const std::time_t& date);

    std::string getName() const;
    double getAmount() const;
    Type getType() const;
    std::time_t getDate() const;

    void setName(const std::string& newName);
    void setAmount(double newAmount);
    void setType(Type newType);
    void setDate(const std::time_t& newDate);

    static std::string typeToString(Type type);
    static Type stringToType(const std::string& typeStr);

private:
    std::string name;
    double amount;
    Type type;
    std::time_t date;
};

#endif // TRANSACTION_H
