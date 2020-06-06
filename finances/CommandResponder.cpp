#include "CommandResponder.hpp"
#include <sstream>
#include <algorithm>

namespace finances {
CommandResponder::CommandResponder(Model &model, View &view)
    : model{model}, view{view} {}

static auto integer(const std::string &s) -> int { return std::stoi(s); }

static auto hundredthsInteger(const std::string &s) -> int {
    return integer(s) * 100;
}

static auto twoDecimalPlaces(const std::string &s) -> std::string {
    return s + std::string(2 - std::min(s.size(), 2UL), '0');
}

static auto hundredths(const std::string &s) -> int {
    const auto decimal{s.find('.')};
    if (decimal == std::string::npos)
        return hundredthsInteger(s);
    const auto *const sign{s.front() == '-' ? "-" : ""};
    const auto beforeDecimalMark{s.substr(0, decimal)};
    const auto firstDecimalPlace{decimal + 1};
    const auto afterDecimalMark{s.substr(firstDecimalPlace)};
    return hundredthsInteger(beforeDecimalMark) +
        integer(sign + twoDecimalPlaces(afterDecimalMark));
}

static auto next(std::stringstream &s) -> std::string {
    std::string next;
    s >> next;
    return next;
}

static auto matches(const std::string &a, const std::string &b) -> bool {
    return a == b;
}

static auto matches(const std::string &a, Command c) -> bool {
    return matches(a, name(c));
}

static auto amount(std::stringstream &stream) -> Amount {
    return Amount{hundredths(next(stream))};
}

static auto transaction(std::stringstream &stream) -> Transaction {
    const auto amount_{amount(stream)};
    auto label{next(stream)};
    auto date{next(stream)};
    return {amount_, std::move(label), std::move(date)};
}

static void show(View &view, const Transactions &t) { view.show(t); }

static auto date(const std::string &first, const std::string &month,
    const std::string &year) -> std::string {
    if (first.find('/') != std::string::npos)
        return first;
    return month + '/' + first + '/' + year;
}

static void add(Model &model, const Transaction &t) { model.add(t); }

void CommandResponder::enter(const std::string &s) {
    try {
        std::stringstream stream{s};
        const auto command{next(stream)};
        if (matches(command, Command::print))
            show(view, model.transactions());
        else if (matches(command, Command::printVerified))
            show(view, model.verifiedTransactions());
        else if (matches(command, Command::printUnverified))
            show(view, model.unverifiedTransactions());
        else if (matches(command, Command::netIncome))
            view.show(model.netIncome());
        else if (matches(command, Command::verify))
            model.verify(amount(stream));
        else if (matches(command, Command::add))
            add(model, transaction(stream));
        else if (matches(command, Command::remove))
            model.remove(transaction(stream));
        else if (matches(command, Command::month))
            state = CommandState::aboutToSetMonth;
        else if (state == CommandState::aboutToSetMonth) {
            month = command;
            state = CommandState::aboutToSetYear;
        } else if (state == CommandState::aboutToSetYear) {
            year = command;
            state = CommandState::normal;
        } else if (state ==
            CommandState::aboutToEnterDateForAddingTransaction) {
            transactionToAdd.date = date(command, month, year);
            add(model, transactionToAdd);
            state = CommandState::normal;
        } else if (state ==
            CommandState::aboutToEnterLabelForAddingTransaction) {
            transactionToAdd.label = command;
            state = CommandState::aboutToEnterDateForAddingTransaction;
        } else {
            transactionToAdd.amount = Amount{hundredths(command)};
            state = CommandState::aboutToEnterLabelForAddingTransaction;
        }
    } catch (const std::invalid_argument &) {
    }
}

auto CommandResponder::prompt() -> Prompt {
    return Prompt{finances::prompt(state), level(state)};
}
}
