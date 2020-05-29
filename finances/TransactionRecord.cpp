#include "TransactionRecord.hpp"
#include <algorithm>
#include <numeric>
#include <functional>
#include <utility>

namespace finances {
constexpr auto begin(const VerifiableTransactions &v) { return v.begin(); }

constexpr auto end(const VerifiableTransactions &v) { return v.end(); }

static auto verified(const VerifiableTransaction &t) -> bool {
    return t.verified;
}

static auto unverified(const VerifiableTransaction &t) -> bool {
    return !verified(t);
}

static auto amountMatches(const Transaction &t, int x) -> bool {
    return amount(t).cents == x;
}

static void addTo(Transactions &transactions, const Transaction &t) {
    transactions.push_back(t);
}

static auto found(VerifiableTransactions::iterator it,
    const VerifiableTransactions &t) -> bool {
    return it != end(t);
}

static auto findIf(VerifiableTransactions &transactions,
    const std::function<bool(const VerifiableTransaction &)> &f) {
    return std::find_if(begin(transactions), end(transactions), f);
}

static auto unverifiedTransaction(const Transaction &t)
    -> VerifiableTransaction {
    VerifiableTransaction v;
    static_cast<Transaction &>(v) = t;
    v.verified = false;
    return v;
}

TransactionRecord::TransactionRecord(EventListener &listener)
    : listener{listener} {}

void TransactionRecord::add(const Transaction &t) {
    verifiableTransactions.push_back(unverifiedTransaction(t));
    listener.added(t);
}

static auto operator==(const Transaction &a, const Transaction &b) -> bool {
    return a.amount.cents == b.amount.cents && a.date == b.date &&
        a.label == b.label;
}

void TransactionRecord::remove(const Transaction &transaction) {
    const auto maybe{std::find(begin(verifiableTransactions),
        end(verifiableTransactions), transaction)};
    if (found(maybe, verifiableTransactions)) {
        if (verified(*maybe))
            verify(amount(*maybe));
        verifiableTransactions.erase(maybe);
    }
}

static void forEach(const VerifiableTransactions &transactions,
    const std::function<void(const VerifiableTransaction &)> &f) {
    std::for_each(begin(transactions), end(transactions), f);
}

static auto collectIf(const VerifiableTransactions &transactions,
    const std::function<bool(const VerifiableTransaction &)> &f)
    -> Transactions {
    Transactions collected;
    forEach(transactions, [&](auto transaction) {
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
    forEach(verifiableTransactions,
        [&](auto transaction) { addTo(transactions, transaction); });
    return transactions;
}

auto TransactionRecord::netIncome() -> NetIncome {
    NetIncome netIncome{};
    netIncome.cents = std::accumulate(begin(verifiableTransactions),
        end(verifiableTransactions), 0,
        [](auto net, auto t) { return net + amount(t).cents; });
    return netIncome;
}

void TransactionRecord::verify(Amount amount) {
    const auto maybe{findIf(verifiableTransactions, [=](auto t) {
        return amountMatches(t, amount.cents) && unverified(t);
    })};
    if (found(maybe, verifiableTransactions)) {
        maybe->verified = true;
        listener.verified(*maybe);
    }
}
}
