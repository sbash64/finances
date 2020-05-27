#ifndef FINANCES_INCLUDE_FINANCES_TRANSACTION_HPP_
#define FINANCES_INCLUDE_FINANCES_TRANSACTION_HPP_

#include <string>
#include <vector>

namespace finances {
struct Amount {
    int cents;
};

struct NetIncome : Amount {};

struct Transaction {
    Amount amount;
    std::string label;
    std::string date;
};

using Transactions = std::vector<Transaction>;

constexpr auto amount(const Transaction &t) { return t.amount; }

constexpr auto label(const Transaction &t) -> auto & { return t.label; }

constexpr auto date(const Transaction &t) -> auto & { return t.date; }
}

#endif
