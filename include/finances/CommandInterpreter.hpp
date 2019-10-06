#ifndef FINANCES_COMMANDINTERPRETER_HPP_
#define FINANCES_COMMANDINTERPRETER_HPP_

#include "Transaction.hpp"
#include <sstream>

namespace finances {
class ITransactionRecord {
public:
    virtual ~ITransactionRecord() = default;
    virtual void add(const Transaction &) = 0;
    virtual Transactions all() = 0;
};

class Printer {
public:
    virtual ~Printer() = default;
    virtual void print(const Transactions &) = 0;
};

int integer(const std::string &s) {
    return std::stoi(s);
}

int toHundredthsNoDecimal(const std::string &s) {
    return integer(s) * 100;
}

int toHundredths(const std::string &s) {
    auto decimal = s.find('.');
    if (decimal == std::string::npos)
        return toHundredthsNoDecimal(s);
    auto sign = ' ';
    if (s.front() == '-')
        sign = '-';
    auto beforeDecimal = s.substr(0, decimal);
    auto afterDecimal = sign + s.substr(decimal + 1);
    return toHundredthsNoDecimal(beforeDecimal) + integer(afterDecimal);
}

std::string next(std::stringstream &s) {
    std::string next_;
    s >> next_;
    return next_;
}

class CommandInterpreter {
    ITransactionRecord &record;
    Printer &printer;
public:
    CommandInterpreter(
        ITransactionRecord &record,
        Printer &printer
    ) :
        record{record},
        printer{printer} {}

    void execute(const std::string &s) {
        std::stringstream stream{s};
        auto command = next(stream);
        if (command == "print")
            printer.print(record.all());
        else {
            auto amount = next(stream);
            auto label = next(stream);
            auto date = next(stream);
            record.add({
                toHundredths(amount),
                label,
                date
            });
        }
    }
};
}

#endif
