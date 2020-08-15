#include "ItemizedFormatter.hpp"
#include <string>

namespace sbash64::finances {
static auto string(int x) -> std::string { return std::to_string(x); }

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

static auto format(Amount x) -> std::string {
    return concatenate(
        beforeDecimal(x.cents), concatenate(".", afterDecimal(x.cents)));
}

static auto formatTransaction(const Transaction &t) -> std::string {
    return concatenate(format(amount(t)),
        withLeadingSpace(concatenate(t.label, withLeadingSpace(t.date))));
}

static void append(std::string &s, const std::string &what) { s += what; }

auto ItemizedFormatter::format(const Transactions &transactions)
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

auto ItemizedFormatter::format(const NetIncome &x) -> std::string {
    return concatenate("Net Income: ", finances::format(x));
}
}
