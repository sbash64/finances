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
    auto afterDecimal = sign + s.substr(decimal + 1);
    return toHundredthsNoDecimal(beforeDecimal) + integer(afterDecimal);
}

static std::string next(std::stringstream &s) {
    std::string next_;
    s >> next_;
    return next_;
}

static bool matches(const std::string &a, const std::string &b) {
    return a == b;
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

void Presenter::execute(const std::string &s) {
    std::stringstream stream{s};
    auto command = next(stream);
    try {
        if (matches(command, "print"))
            view.showTransactions(model.transactions());
        else if (matches(command, "printverified"))
            view.showTransactions(model.verifiedTransactions());
        else if (matches(command, "net"))
            view.showNetIncome(model.netIncome());
        else if (matches(command, "verify"))
            model.verify(amount(stream));
        else if (matches(command, "add"))
            model.add(transaction(stream));
        else if (matches(command, "remove"))
            model.remove(transaction(stream));
    } catch (const std::exception &) {

    }
}
}
