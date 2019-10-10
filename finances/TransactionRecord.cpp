#include "TransactionRecord.hpp"
#include <algorithm>
#include <numeric>
#include <functional>

namespace finances {
constexpr auto begin(const Transactions &v) {
    return v.begin();
}

constexpr auto end(const Transactions &v) {
    return v.end();
}

constexpr auto end(const VerifiableTransactions &v) {
    return v.end();
}

constexpr auto &transaction(const VerifiableTransaction &t) {
    return t.transaction;
}

static auto find_if(
    VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f
) {
    return std::find_if(
        std::begin(transactions),
        end(transactions),
        [=](auto t) { return f(t); }
    );
}

void TransactionRecord::add(const Transaction &t) {
    verifiableTransactions_.push_back({t, false});
}

void TransactionRecord::remove(const Transaction &transaction_) {
    auto found_ = find_if(
        verifiableTransactions_,
        [=](auto t) { return transaction(t) == transaction_; }
    );
    if (found_ != end(verifiableTransactions_))
        verifiableTransactions_.erase(found_);
}

static bool amountMatches(const Transaction &t, int amount_) {
    return amount(t) == amount_;
}

Transactions TransactionRecord::findByAmount(int amount) {
    Transactions found;
    for (auto t : verifiableTransactions_)
        if (amountMatches(transaction(t), amount))
            found.push_back(transaction(t));
    return found;
}

Transactions TransactionRecord::transactions() {
    Transactions found;
    for (auto t : verifiableTransactions_)
        found.push_back(transaction(t));
    return found;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(verifiableTransactions_),
        end(verifiableTransactions_),
        0,
        [](auto net, auto t) { return net + amount(transaction(t)); }
    );
}

void TransactionRecord::verify(int amount_) {
    auto found = find_if(
        verifiableTransactions_,
        [=](auto t) { return amountMatches(transaction(t), amount_); }
    );
    found->verified = true;
}

Transactions TransactionRecord::verifiedTransactions() {
    auto found = find_if(
        verifiableTransactions_,
        [=](auto t) { return t.verified; }
    );
    if (found == end(verifiableTransactions_))
        return {};
    return { found->transaction };
}
}
