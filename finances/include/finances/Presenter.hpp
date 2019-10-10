#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "Transaction.hpp"
#include <string>

namespace finances {
class Model {
public:
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual Transactions transactions() = 0;
    virtual int netIncome() = 0;
    virtual void verify(int amount) = 0;
};

class View {
public:
    virtual ~View() = default;
    virtual void showTransactions(const Transactions &) = 0;
    virtual void showNetIncome(int) = 0;
};

class Presenter {
    Model &model;
    View &view;
public:
    Presenter(Model &, View &);
    void execute(const std::string &);
};
}

#endif
