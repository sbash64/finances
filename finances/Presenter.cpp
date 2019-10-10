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

void Presenter::execute(const std::string &s) {
    std::stringstream stream{s};
    auto command = next(stream);
    if (matches(command, "print"))
        view.showTransactions(model.transactions());
    else if (matches(command, "net"))
        view.showNetIncome(model.netIncome());
    else if (matches(command, "verify")) {
        auto amount = next(stream);
        model.verify(toHundredths(amount));
    }
    else if (matches(command, "add")) {
        auto amount = next(stream);
        auto label = next(stream);
        auto date = next(stream);
        model.add({
            toHundredths(amount),
            label,
            date
        });
    }
}
}
