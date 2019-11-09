#include "ItemizedFormatter.hpp"
#include <string>

namespace finances {
auto string(int x) -> std::string { return std::to_string(x); }

static auto hundreds(int x) -> int { return x / 100; }

static auto remainingHundredths(int x) -> int {
    return std::abs(x - hundreds(x) * 100);
}

static auto concatenate(const std::string &s1, const std::string &s2)
    -> std::string {
    return s1 + s2;
}

static auto withLeadingSpace(const std::string &s) -> std::string {
    return concatenate(" ", s);
}

static auto twoDigits(int x) -> std::string {
    return concatenate(x < 10 ? "0" : "", string(x));
}

static auto afterDecimal(int x) -> std::string {
    return twoDigits(remainingHundredths(x));
}

static auto beforeDecimal(int x) -> std::string { return string(hundreds(x)); }

static auto formatAmount(int x) -> std::string {
    return concatenate(beforeDecimal(x), concatenate(".", afterDecimal(x)));
}

static auto formatTransaction(const Transaction &t) -> std::string {
    return concatenate(formatAmount(amount(t)),
        withLeadingSpace(concatenate(t.label, withLeadingSpace(t.date))));
}

static void append(std::string &s, const std::string &what) { s += what; }

auto ItemizedFormatter::formatTransactions(const Transactions &transactions)
    -> std::string {
    std::string formatted;
    bool first = true;
    for (const auto &transaction : transactions) {
        if (!first)
            append(formatted, "\n");
        append(formatted, formatTransaction(transaction));
        first = false;
    }
    return formatted;
}

auto ItemizedFormatter::formatNetIncome(int x) -> std::string {
    return concatenate("Net Income: ", formatAmount(x));
}
}
