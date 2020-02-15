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

static auto verified(const VerifiableTransaction &t) -> bool {
    return t.verified;
}

static auto unverified(const VerifiableTransaction &t) -> bool {
    return !verified(t);
}

static auto amountMatches(const Transaction &t, int x) -> bool {
    return amount(t) == x;
}

static void addTo(Transactions &t, const VerifiableTransaction &vt) {
    t.push_back(vt);
}

static auto found(VerifiableTransactions::iterator it,
    const VerifiableTransactions &t) -> bool {
    return it != end(t);
}

static auto findIf(VerifiableTransactions &transactions,
    std::function<bool(const VerifiableTransaction &)> f) {
    return std::find_if(begin(transactions), end(transactions), std::move(f));
}

static auto unverifiedTransaction(const Transaction &t)
    -> VerifiableTransaction {
    VerifiableTransaction v;
    static_cast<Transaction &>(v) = t;
    v.verified = false;
    return v;
}

void TransactionRecord::add(const Transaction &t) {
    verifiableTransactions.push_back(unverifiedTransaction(t));
    listener->added(t);
}

void TransactionRecord::subscribe(EventListener *e) { listener = e; }

void TransactionRecord::remove(const Transaction &transaction) {
    const auto maybe{std::find(begin(verifiableTransactions),
        end(verifiableTransactions), transaction)};
    if (found(maybe, verifiableTransactions)) {
        if (verified(*maybe))
            verify(amount(*maybe));
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
        [](auto net, auto t) { return net + amount(t); });
}

void TransactionRecord::verify(int amount) {
    const auto maybe{findIf(verifiableTransactions,
        [=](auto t) { return amountMatches(t, amount) && unverified(t); })};
    if (found(maybe, verifiableTransactions)) {
        maybe->verified = true;
        listener->verified(*maybe);
    }
}
}
