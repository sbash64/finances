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

std::string ItemizedFormatter::formatTransactions(
    const Transactions &transactions
) {
    std::string formatted;
    bool first = true;
    for (auto transaction : transactions) {
        if (!first)
            formatted += '\n';
        auto amountBeforeDecimal = hundreds(amount(transaction));
        auto amountAfterDecimal = remainder(amount(transaction));
        auto leadingZero = amountAfterDecimal < 10 ? "0" : "";
        auto beforeDecimal = string(amountBeforeDecimal);
        auto afterDecimal = leadingZero + string(amountAfterDecimal);
        formatted +=
            beforeDecimal + "." + afterDecimal + " " +
            transaction.label + " " +
            transaction.date;
        first = false;
    }
    return formatted;
}

std::string ItemizedFormatter::formatNetIncome(int x) {
    auto amountBeforeDecimal = hundreds(x);
    auto amountAfterDecimal = remainder(x);
    auto leadingZero =  "";
    if (amountAfterDecimal < 10)
        leadingZero = "0";
    auto beforeDecimal = string(amountBeforeDecimal);
    auto afterDecimal = leadingZero + string(amountAfterDecimal);
    return "Net Income: " + beforeDecimal + "." + afterDecimal;
}
}
