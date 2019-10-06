#include "TransactionRecord.hpp"
#include <algorithm>
#include <numeric>

namespace finances {
void TransactionRecord::add(const Transaction &t) {
    transactions.push_back(t);
}

void TransactionRecord::remove(const Transaction &) {
    transactions.pop_back();
}

constexpr auto begin(const Transactions &v) {
    return v.begin();
}

constexpr auto end(const Transactions &v) {
    return v.end();
}

Transactions TransactionRecord::findByAmount(int amount_) {
    Transactions found;
    std::copy_if(
        begin(transactions),
        end(transactions),
        std::back_inserter(found),
        [=](auto t) { return amount(t) == amount_; }
    );
    return found;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(transactions),
        end(transactions),
        0,
        [](auto net, auto t) { return net + t.amount; }
    );
}
}