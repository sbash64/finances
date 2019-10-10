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
    virtual void showTransactions(const Transactions &) = 0;
    virtual void showNetIncome(int) = 0;
};

class CommandInterpreter {
    Model &model;
    View &view;
public:
    CommandInterpreter(Model &, View &);
    void execute(const std::string &);
};
}

#endif
