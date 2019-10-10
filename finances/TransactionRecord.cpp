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

static bool verified(const VerifiableTransaction &t) {
    return t.verified;
}

static bool amountMatches(const Transaction &t, int amount_) {
    return amount(t) == amount_;
}

static bool amountMatches(const VerifiableTransaction &t, int amount_) {
    return amountMatches(transaction(t), amount_);
}

static void addTo(Transactions &t, const VerifiableTransaction &vt) {
    t.push_back(transaction(vt));
}

static bool found(
    VerifiableTransactions::iterator it,
    const VerifiableTransactions &t
) {
    return it != end(t);
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
    verifiableTransactions.push_back({t, false});
}

void TransactionRecord::remove(const Transaction &transaction_) {
    auto found_ = find_if(
        verifiableTransactions,
        [=](auto t) { return transaction(t) == transaction_; }
    );
    if (found(found_, verifiableTransactions))
        verifiableTransactions.erase(found_);
}

Transactions TransactionRecord::findByAmount(int amount) {
    Transactions found;
    for (auto transaction : verifiableTransactions)
        if (amountMatches(transaction, amount))
            addTo(found, transaction);
    return found;
}

Transactions TransactionRecord::verifiedTransactions() {
    Transactions found;
    for (auto transaction : verifiableTransactions)
        if (verified(transaction))
            addTo(found, transaction);
    return found;
}

Transactions TransactionRecord::transactions() {
    Transactions transactions;
    for (auto transaction : verifiableTransactions)
        addTo(transactions, transaction);
    return transactions;
}

int TransactionRecord::netIncome() {
    return std::accumulate(
        begin(verifiableTransactions),
        end(verifiableTransactions),
        0,
        [](auto net, auto t) { return net + amount(transaction(t)); }
    );
}

void TransactionRecord::verify(int amount) {
    auto found = find_if(
        verifiableTransactions,
        [=](auto t) { return amountMatches(t, amount); }
    );
    found->verified = true;
}
}
