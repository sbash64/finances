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
    transactions.push_back(t);
}

void TransactionRecord::remove(const Transaction &t) {
    auto found = std::find(
        begin(transactions),
        end(transactions),
        t
    );
    if (found != end(transactions))
        transactions.erase(found);
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

Transactions TransactionRecord::getAll() {
    return transactions;
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