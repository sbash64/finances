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

static bool found(
    VerifiableTransactions::iterator it,
    const VerifiableTransactions &t
) {
    return it != end(t);
}

void TransactionRecord::remove(const Transaction &transaction_) {
    auto found_ = find_if(
        verifiableTransactions_,
        [=](auto t) { return transaction(t) == transaction_; }
    );
    if (found(found_, verifiableTransactions_))
        verifiableTransactions_.erase(found_);
}

static bool amountMatches(const Transaction &t, int amount_) {
    return amount(t) == amount_;
}

static void addTo(Transactions &t, const VerifiableTransaction &vt) {
    t.push_back(transaction(vt));
}

Transactions TransactionRecord::findByAmount(int amount) {
    Transactions found;
    for (auto t : verifiableTransactions_)
        if (amountMatches(transaction(t), amount))
            addTo(found, t);
    return found;
}

Transactions TransactionRecord::transactions() {
    Transactions transactions;
    for (auto t : verifiableTransactions_)
        addTo(transactions, t);
    return transactions;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(verifiableTransactions_),
        end(verifiableTransactions_),
        0,
        [](auto net, auto t) { return net + amount(transaction(t)); }
    );
}

static bool verified(const VerifiableTransaction &t) {
    return t.verified;
}

void TransactionRecord::verify(int amount_) {
    auto found = find_if(
        verifiableTransactions_,
        [=](auto t) { return amountMatches(transaction(t), amount_); }
    );
    found->verified = true;
}

Transactions TransactionRecord::verifiedTransactions() {
    Transactions found;
    for (auto t : verifiableTransactions_)
        if (verified(t))
            addTo(found, t);
    return found;
}
}
