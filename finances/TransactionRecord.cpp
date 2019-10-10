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

constexpr auto end(const std::vector<VerifiableTransaction> &v) {
    return v.end();
}

static auto find_if(
    std::vector<VerifiableTransaction> &transactions,
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

void TransactionRecord::remove(const Transaction &t) {
    auto found_ = find_if(
        verifiableTransactions_,
        [=](auto t_) { return t_.transaction == t; }
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
        if (amountMatches(t.transaction, amount))
            found.push_back(t.transaction);
    return found;
}

Transactions TransactionRecord::transactions() {
    Transactions found;
    for (auto t : verifiableTransactions_)
        found.push_back(t.transaction);
    return found;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(verifiableTransactions_),
        end(verifiableTransactions_),
        0,
        [](auto net, auto t) { return net + amount(t.transaction); }
    );
}

void TransactionRecord::verify(int amount_) {
    auto found = find_if(
        verifiableTransactions_,
        [=](auto t) { return amountMatches(t.transaction, amount_); }
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
