#ifndef FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_
#define FINANCES_INCLUDE_FINANCES_COMMANDRESPONDER_HPP_

#include "Transaction.hpp"
#include "Responder.hpp"
#include "Model.hpp"
#include "View.hpp"

namespace sbash64::finances {
enum class Command {
    print,
    printVerified,
    printUnverified,
    add,
    remove,
    verify,
    netIncome,
    month
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
    case (Command::month):
        return "month";
    }
    return "";
}

enum class CommandState {
    normal,
    aboutToEnterLabelForAddingTransaction,
    aboutToEnterDateForAddingTransaction,
    aboutToSetMonth,
    aboutToSetYear
};

constexpr auto prompt(CommandState c) -> const char * {
    switch (c) {
    case (CommandState::normal):
        return "finances";
    case (CommandState::aboutToEnterLabelForAddingTransaction):
        return "label";
    case (CommandState::aboutToEnterDateForAddingTransaction):
        return "date";
    case (CommandState::aboutToSetMonth):
        return "month";
    case (CommandState::aboutToSetYear):
        return "year";
    }
    return "";
}

constexpr auto level(CommandState c) -> Responder::Prompt::Level {
    switch (c) {
    case (CommandState::normal):
        return Responder::Prompt::Level::primary;
    case (CommandState::aboutToEnterLabelForAddingTransaction):
    case (CommandState::aboutToEnterDateForAddingTransaction):
    case (CommandState::aboutToSetMonth):
    case (CommandState::aboutToSetYear):
        return Responder::Prompt::Level::secondary;
    }
    return {};
}

class CommandResponder : public Responder {
  public:
    CommandResponder(Model &, View &);
    void enter(const std::string &) override;
    auto prompt() -> Prompt override;

  private:
    Model &model;
    View &view;
    Transaction transactionToAdd;
    std::string month{};
    std::string year{};
    CommandState state{};
};
}

#endif
