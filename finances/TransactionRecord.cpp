#include "TransactionRecord.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>

namespace finances {
constexpr auto begin(const Transactions &v) { return v.begin(); }

constexpr auto end(const Transactions &v) { return v.end(); }

constexpr auto begin(const VerifiableTransactions &v) { return v.begin(); }

constexpr auto end(const VerifiableTransactions &v) { return v.end(); }

constexpr auto transaction(const VerifiableTransaction &t) -> auto & {
    return t.transaction;
}

static auto verified(const VerifiableTransaction &t) -> bool {
    return t.verified;
}

static auto unverified(const VerifiableTransaction &t) -> bool {
    return !verified(t);
}

static auto amountMatches(const Transaction &t, int amount_) -> bool {
    return amount(t) == amount_;
}

static auto amountMatches(const VerifiableTransaction &t, int amount_) -> bool {
    return amountMatches(transaction(t), amount_);
}

static void addTo(Transactions &t, const VerifiableTransaction &vt) {
    t.push_back(transaction(vt));
}

static auto found(VerifiableTransactions::iterator it,
    const VerifiableTransactions &t) -> bool {
    return it != end(t);
}

static auto findIf(VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f) {
    return std::find_if(begin(transactions), end(transactions), std::move(f));
}

void TransactionRecord::add(const Transaction &t) {
    verifiableTransactions.push_back({t, false});
}

void TransactionRecord::subscribe(EventListener *e) { listener = e; }

void TransactionRecord::remove(const Transaction &transaction_) {
    auto maybe = findIf(verifiableTransactions,
        [&](auto t) { return transaction(t) == transaction_; });
    if (found(maybe, verifiableTransactions)) {
        if (verified(*maybe))
            verify(maybe->transaction.amount);
        verifiableTransactions.erase(maybe);
    }
}

static void for_each(const VerifiableTransactions &transactions,
    std::function<void(const VerifiableTransaction &)> f) {
    std::for_each(begin(transactions), end(transactions), std::move(f));
}

static auto collectIf(const VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f) -> Transactions {
    Transactions collected;
    for_each(transactions, [&](auto transaction) {
        if (f(transaction))
            addTo(collected, transaction);
    });
    return collected;
}

auto TransactionRecord::verifiedTransactions() -> Transactions {
    return collectIf(verifiableTransactions, verified);
}

auto TransactionRecord::unverifiedTransactions() -> Transactions {
    return collectIf(verifiableTransactions, unverified);
}

auto TransactionRecord::transactions() -> Transactions {
    Transactions transactions;
    for_each(verifiableTransactions,
        [&](auto transaction) { addTo(transactions, transaction); });
    return transactions;
}

auto TransactionRecord::netIncome() -> int {
    return std::accumulate(begin(verifiableTransactions),
        end(verifiableTransactions), 0,
        [](auto net, auto t) { return net + amount(transaction(t)); });
}

void TransactionRecord::verify(int amount) {
    auto found_ = findIf(verifiableTransactions,
        [=](auto t) { return amountMatches(t, amount) && unverified(t); });
    if (found(found_, verifiableTransactions)) {
        listener->verified(found_->transaction);
        found_->verified = true;
    }
}
}
