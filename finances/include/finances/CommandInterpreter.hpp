#ifndef FINANCES_INCLUDE_FINANCES_COMMANDINTERPRETER_HPP_
#define FINANCES_INCLUDE_FINANCES_COMMANDINTERPRETER_HPP_

#include "Transaction.hpp"
#include <string>

namespace finances {
class ITransactionRecord {
public:
    virtual ~ITransactionRecord() = default;
    virtual void add(const Transaction &) = 0;
    virtual Transactions all() = 0;
    virtual int netIncome() = 0;
};

class Printer {
public:
    virtual ~Printer() = default;
    virtual void printTransactions(const Transactions &) = 0;
    virtual void printNetIncome(int) = 0;
};

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
    void execute(const std::string &);
};
}

#endif
