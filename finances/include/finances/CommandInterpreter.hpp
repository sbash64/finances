#ifndef FINANCES_INCLUDE_FINANCES_COMMANDINTERPRETER_HPP_
#define FINANCES_INCLUDE_FINANCES_COMMANDINTERPRETER_HPP_

#include "Transaction.hpp"
#include <string>

namespace finances {
class Model {
public:
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual Transactions all() = 0;
    virtual int netIncome() = 0;
};

class View {
public:
    virtual ~View() = default;
    virtual void printTransactions(const Transactions &) = 0;
    virtual void printNetIncome(int) = 0;
};

class CommandInterpreter {
    Model &record;
    View &printer;
public:
    CommandInterpreter(
        Model &record,
        View &printer
    ) :
        record{record},
        printer{printer} {}
    void execute(const std::string &);
};
}

#endif
