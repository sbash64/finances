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

constexpr auto begin(const VerifiableTransactions &v) {
    return v.begin();
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

static bool unverified(const VerifiableTransaction &t) {
    return !verified(t);
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

static auto findIf(
    VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f
) {
    return std::find_if(begin(transactions), end(transactions), f);
}

void TransactionRecord::add(const Transaction &t) {
    verifiableTransactions.push_back({t, false});
}

void TransactionRecord::remove(const Transaction &transaction_) {
    auto maybe = findIf(
        verifiableTransactions,
        [&](auto t) { return transaction(t) == transaction_; }
    );
    if (found(maybe, verifiableTransactions))
        verifiableTransactions.erase(maybe);
}

static void for_each(
    const VerifiableTransactions &transactions,
    std::function<void(const VerifiableTransaction &)> f
) {
    std::for_each(begin(transactions), end(transactions), f);
}

static Transactions collectIf(
    const VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f
) {
    Transactions collected;
    for_each(
        transactions,
        [&](auto transaction) {
            if (f(transaction))
                addTo(collected, transaction);
        }
    );
    return collected;
}

Transactions TransactionRecord::findByAmount(int amount) {
    return collectIf(
        verifiableTransactions,
        [=](auto transaction) {
            return amountMatches(transaction, amount);
        }
    );
}

Transactions TransactionRecord::verifiedTransactions() {
    return collectIf(verifiableTransactions, verified);
}

Transactions TransactionRecord::unverifiedTransactions() {
    return collectIf(verifiableTransactions, unverified);
}

Transactions TransactionRecord::transactions() {
    Transactions transactions;
    for_each(
        verifiableTransactions,
        [&](auto transaction) {
            addTo(transactions, transaction);
        }
    );
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
    auto found_ = findIf(
        verifiableTransactions,
        [=](auto t) { return amountMatches(t, amount) && unverified(t); }
    );
    if (found(found_, verifiableTransactions))
        found_->verified = true;
}
}
