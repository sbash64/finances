#include "Presenter.hpp"
#include <sstream>

namespace finances {
Presenter::Presenter(
    Model &record,
    View &printer
) :
    model{record},
    view{printer} {}

static int integer(const std::string &s) {
    return std::stoi(s);
}

static int hundredthsInteger(const std::string &s) {
    return integer(s) * 100;
}

static std::string twoDecimalPlaces(std::string s) {
    return s + std::string(2 - s.size(), '0');
}

static int hundredths(const std::string &s) {
    auto decimal = s.find('.');
    if (decimal == std::string::npos)
        return hundredthsInteger(s);
    auto sign = s.front() == '-' ? "-" : "";
    auto beforeDecimalMark = s.substr(0, decimal);
    auto firstDecimalPlace = decimal + 1;
    auto afterDecimalMark = s.substr(firstDecimalPlace);
    return
        hundredthsInteger(beforeDecimalMark) +
        integer(sign + twoDecimalPlaces(afterDecimalMark));
}

static std::string next(std::stringstream &s) {
    std::string next_;
    s >> next_;
    return next_;
}

static bool matches(const std::string &a, const std::string &b) {
    return a == b;
}

static bool matches(const std::string &a, Command c) {
    return matches(a, name(c));
}

static int amount(std::stringstream &stream) {
    return hundredths(next(stream));
}

static Transaction transaction(std::stringstream &stream) {
    auto amount_ = amount(stream);
    auto label = next(stream);
    auto date = next(stream);
    return {amount_, label, date};
}

static void showTransactions(View &view, const Transactions &t) {
    view.showTransactions(t);
}

static void execute(Model &model, View &view, const std::string &s) {
    std::stringstream stream{s};
    auto command = next(stream);
    if (matches(command, Command::print))
        showTransactions(view, model.transactions());
    else if (matches(command, Command::printVerified))
        showTransactions(view, model.verifiedTransactions());
    else if (matches(command, Command::printUnverified))
        showTransactions(view, model.unverifiedTransactions());
    else if (matches(command, Command::netIncome))
        view.showNetIncome(model.netIncome());
    else if (matches(command, Command::verify))
        model.verify(amount(stream));
    else if (matches(command, Command::add))
        model.add(transaction(stream));
    else if (matches(command, Command::remove))
        model.remove(transaction(stream));
}

void Presenter::execute(const std::string &s) {
    try {
        ::finances::execute(model, view, s);
    } catch (const std::invalid_argument &) {
    }
}
}
