#include "TransactionRecord.hpp"
#include <algorithm>
#include <numeric>

namespace finances {
constexpr auto begin(const Transactions &v) {
    return v.begin();
}

constexpr auto end(const Transactions &v) {
    return v.end();
}

void TransactionRecord::add(const Transaction &t) {
    transactions_.push_back(t);
}

void TransactionRecord::remove(const Transaction &t) {
    auto found = std::find(
        begin(transactions_),
        end(transactions_),
        t
    );
    if (found != end(transactions_))
        transactions_.erase(found);
}

Transactions TransactionRecord::findByAmount(int amount_) {
    Transactions found;
    std::copy_if(
        begin(transactions_),
        end(transactions_),
        std::back_inserter(found),
        [=](auto t) { return amount(t) == amount_; }
    );
    return found;
}

Transactions TransactionRecord::transactions() {
    return transactions_;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(transactions_),
        end(transactions_),
        0,
        [](auto net, auto t) { return net + t.amount; }
    );
}
}
