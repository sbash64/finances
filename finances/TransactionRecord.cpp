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
    verifiableTransactions_.push_back({t, false});
    verified_.push_back(false);
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
void TransactionRecord::verify(int amount_) {
    auto found = std::find_if(
        std::begin(verifiableTransactions_),
        std::end(verifiableTransactions_),
        [=](auto t) { return amount(t.transaction) == amount_; }
    );
    found->verified = true;
}

Transactions TransactionRecord::verifiedTransactions() {
    auto found = std::find_if(
        std::begin(verifiableTransactions_),
        std::end(verifiableTransactions_),
        [=](auto t) { return t.verified; }
    );
    if (found == verifiableTransactions_.end())
        return {};
    return { found->transaction };
}
}
