#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "Transaction.hpp"
#include <string>

namespace finances {
class Model {
  public:
    class EventListener {
      public:
        virtual ~EventListener() = default;
        virtual void verified(const Transaction &) = 0;
        virtual void added(const Transaction &) = 0;
    };
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual void remove(const Transaction &) = 0;
    virtual void verify(int amount) = 0;
    virtual auto transactions() -> Transactions = 0;
    virtual auto verifiedTransactions() -> Transactions = 0;
    virtual auto unverifiedTransactions() -> Transactions = 0;
    virtual auto netIncome() -> int = 0;
    virtual void subscribe(EventListener *) = 0;
};

class View {
  public:
    virtual ~View() = default;
    virtual void show(const Transactions &) = 0;
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

constexpr auto name(Command c) -> const char * {
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
    }
    return "";
}

class Presenter : Model::EventListener {
  public:
    Presenter(Model &, View &);
    void execute(const std::string &);
    void verified(const Transaction &) override;
    void added(const Transaction &) override;

  private:
    Model &model;
    View &view;
    bool amountEntered{};
    int amountAdding{};
    bool labelEntered{};
    std::string labelAdding{};
};
}

#endif
