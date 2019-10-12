#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "Transaction.hpp"
#include <string>

namespace finances {
class Model {
public:
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual void remove(const Transaction &) = 0;
    virtual Transactions transactions() = 0;
    virtual Transactions verifiedTransactions() = 0;
    virtual Transactions unverifiedTransactions() = 0;
    virtual int netIncome() = 0;
    virtual void verify(int amount) = 0;
};

class View {
public:
    virtual ~View() = default;
    virtual void showTransactions(const Transactions &) = 0;
    virtual void showNetIncome(int) = 0;
};

enum class Command {
    print,
    printVerified,
    printUnverified,
    add,
    remove,
    verify,
    netIncome
};

constexpr const char *name(Command c) {
    switch (c) {
        case (Command::print):
            return "print";
        case (Command::printVerified):
            return "printverified";
        case (Command::printUnverified):
            return "printunverified";
        case (Command::add):
            return "add";
        case (Command::remove):
            return "remove";
        case (Command::verify):
            return "verify";
        case (Command::netIncome):
            return "net";
        default:
            return "";
    }
}

class Presenter {
    Model &model;
    View &view;
public:
    Presenter(Model &, View &);
    void execute(const std::string &);
};
}

#endif
