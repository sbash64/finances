#include "CommandInterpreter.hpp"

namespace finances {
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

void CommandInterpreter::execute(const std::string &s) {
    std::stringstream stream{s};
    auto command = next(stream);
    if (command == "print")
        printer.print(record.all());
    else if (command == "net")
        printer.printNetIncome(record.netIncome());
    else {
        auto amount = next(stream);
        auto label = next(stream);
        auto date = next(stream);
        record.add({
            toHundredths(amount),
            label,
            date
        });
    }
}
}