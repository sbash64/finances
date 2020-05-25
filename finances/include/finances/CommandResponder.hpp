#ifndef FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_
#define FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_

#include "Transaction.hpp"
#include "Model.hpp"
#include "View.hpp"
#include <string>

namespace finances {
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

class CommandResponder {
  public:
    CommandResponder(Model &, View &);
    void execute(const std::string &);

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
