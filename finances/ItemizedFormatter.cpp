#include "ItemizedFormatter.hpp"
#include <string>

namespace finances {
std::string string(int x) {
    return std::to_string(x);
}

static int hundreds(int x) {
    return x / 100;
}

static int remainingHundredths(int x) {
    return std::abs(x - hundreds(x) * 100);
}

static std::string afterDecimal(int x) {
    auto amountAfterDecimal = remainingHundredths(x);
    return (amountAfterDecimal < 10 ? "0" : "") + string(amountAfterDecimal);
}

static std::string beforeDecimal(int x) {
    return string(hundreds(x));
}

static std::string formatAmount(int x) {
    return beforeDecimal(x) + "." + afterDecimal(x);
}

static std::string formatTransaction(const Transaction &t) {
    return
        formatAmount(amount(t)) + " " +
        t.label + " " +
        t.date;
}

std::string ItemizedFormatter::formatTransactions(
    const Transactions &transactions
) {
    std::string formatted;
    bool first = true;
    for (auto transaction : transactions) {
        if (!first)
            formatted += '\n';
        formatted += formatTransaction(transaction);
        first = false;
    }
    return formatted;
}

std::string ItemizedFormatter::formatNetIncome(int x) {
    return "Net Income: " + formatAmount(x);
}
}
