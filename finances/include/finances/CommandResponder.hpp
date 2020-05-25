#ifndef FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_
#define FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_

#include "Transaction.hpp"
#include "Model.hpp"
#include <string>

namespace finances {
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

class CommandResponder : Model::EventListener {
  public:
    CommandResponder(Model &, View &);
    void execute(const std::string &);
    void verified(const Transaction &) override;
    void added(const Transaction &) override;

    enum class State { normal, amountEntered, labelEntered };

  private:
    Model &model;
    View &view;
    std::string labelAdding{};
    int amountAdding{};
    State state{};
};
}

#endif
