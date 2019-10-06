#include "ItemizedFormatter.hpp"
#include <string>

namespace finances {
std::string string(int x) {
    return std::to_string(x);
}

std::string ItemizedFormatter::formatTransactions(const Transactions &transactions) {
    std::string formatted;
    bool first = true;
    for (auto transaction : transactions) {
        if (!first)
            formatted += '\n';
        auto amountBeforeDecimal = amount(transaction) / 100;
        auto amountAfterDecimal =
            std::abs(amount(transaction) - amountBeforeDecimal * 100);
        auto leadingZero =  "";
        if (amountAfterDecimal < 10)
            leadingZero = "0";
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
}