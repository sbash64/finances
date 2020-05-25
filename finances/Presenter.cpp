#include "Presenter.hpp"
#include <sstream>

namespace finances {
Presenter::Presenter(Model &record, View &printer)
    : model{record}, view{printer} {
    model.subscribe(this);
}

static auto integer(const std::string &s) -> int { return std::stoi(s); }

static auto hundredthsInteger(const std::string &s) -> int {
    return integer(s) * 100;
}

static auto twoDecimalPlaces(const std::string &s) -> std::string {
    return s + std::string(2 - s.size(), '0');
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

static auto amount(std::stringstream &stream) -> int {
    return hundredths(next(stream));
}

static auto transaction(std::stringstream &stream) -> Transaction {
    const auto amount_{amount(stream)};
    auto label{next(stream)};
    auto date{next(stream)};
    return {amount_, std::move(label), std::move(date)};
}

static void show(View &view, const Transactions &t) { view.show(t); }

void Presenter::execute(const std::string &s) {
    try {
        std::stringstream stream{s};
        const auto first{next(stream)};
        if (matches(first, Command::print))
            show(view, model.transactions());
        else if (matches(first, Command::printVerified))
            show(view, model.verifiedTransactions());
        else if (matches(first, Command::printUnverified))
            show(view, model.unverifiedTransactions());
        else if (matches(first, Command::netIncome))
            view.showNetIncome(model.netIncome());
        else if (matches(first, Command::verify))
            model.verify(amount(stream));
        else if (matches(first, Command::add))
            model.add(transaction(stream));
        else if (matches(first, Command::remove))
            model.remove(transaction(stream));
        else if (state == State::labelEntered) {
            model.add({amountAdding, labelAdding, first});
            state = State::normal;
        } else if (state == State::amountEntered) {
            labelAdding = first;
            labelEntered = true;
            state = State::labelEntered;
        } else {
            amountAdding = hundredths(first);
            amountEntered = true;
            state = State::amountEntered;
        }
    } catch (const std::invalid_argument &) {
    }
}

void Presenter::verified(const Transaction &t) { show(view, {t}); }

void Presenter::added(const Transaction &t) { show(view, {t}); }
}
