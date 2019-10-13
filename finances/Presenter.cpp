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

static int toHundredthsNoDecimal(const std::string &s) {
    return integer(s) * 100;
}

static int toHundredths(const std::string &s) {
    auto decimal = s.find('.');
    if (decimal == std::string::npos)
        return toHundredthsNoDecimal(s);
    auto sign = ' ';
    if (s.front() == '-')
        sign = '-';
    auto beforeDecimal = s.substr(0, decimal);
    auto afterDecimal = s.substr(decimal + 1);
    if (afterDecimal.size() == 1)
        afterDecimal += '0';
    return toHundredthsNoDecimal(beforeDecimal) + integer(sign + afterDecimal);
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
    return toHundredths(next(stream));
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
