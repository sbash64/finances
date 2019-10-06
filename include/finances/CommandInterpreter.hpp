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
