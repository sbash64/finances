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

static std::string concatenate(std::string s1, std::string s2) {
    return s1 + s2;
}

static std::string withLeadingSpace(std::string s) {
    return concatenate(" ", std::move(s));
}

static std::string twoDigits(int x) {
    return concatenate(x < 10 ? "0" : "", string(x));
}

static std::string afterDecimal(int x) {
    return twoDigits(remainingHundredths(x));
}

static std::string beforeDecimal(int x) {
    return string(hundreds(x));
}

static std::string formatAmount(int x) {
    return concatenate(
        beforeDecimal(x),
        concatenate(".", afterDecimal(x))
    );
}

static std::string formatTransaction(const Transaction &t) {
    return
        concatenate(
            formatAmount(amount(t)),
            withLeadingSpace(concatenate(
                t.label,
                withLeadingSpace(t.date)
            ))
        );
}

static void append(std::string &s, const std::string &what) {
    s += what;
}

std::string ItemizedFormatter::formatTransactions(
    const Transactions &transactions
) {
    std::string formatted;
    bool first = true;
    for (auto transaction : transactions) {
        if (!first)
            append(formatted, "\n");
        append(formatted, formatTransaction(transaction));
        first = false;
    }
    return formatted;
}

std::string ItemizedFormatter::formatNetIncome(int x) {
    return "Net Income: " + formatAmount(x);
}
}
