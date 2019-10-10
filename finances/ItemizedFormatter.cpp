#include "ItemizedFormatter.hpp"
#include <string>

namespace finances {
std::string string(int x) {
    return std::to_string(x);
}

static int hundreds(int x) {
    return x / 100;
}

static int remainder(int x) {
    return std::abs(x - hundreds(x) * 100);
}

static std::string afterDecimal(int x) {
    auto amountAfterDecimal = remainder(x);
    return (amountAfterDecimal < 10 ? "0" : "") + string(amountAfterDecimal);
}

static std::string beforeDecimal(int x) {
    return string(hundreds(x));
}

std::string ItemizedFormatter::formatTransactions(
    const Transactions &transactions
) {
    std::string formatted;
    bool first = true;
    for (auto transaction : transactions) {
        if (!first)
            formatted += '\n';
        formatted +=
            beforeDecimal(amount(transaction)) + "." +
            afterDecimal(amount(transaction)) + " " +
            transaction.label + " " +
            transaction.date;
        first = false;
    }
    return formatted;
}

std::string ItemizedFormatter::formatNetIncome(int x) {
    return "Net Income: " + beforeDecimal(x) + "." + afterDecimal(x);
}
}
