#include "TransactionRecord.hpp"

namespace finances {
int amount(const Transaction &t) {
    return t.amount;
}

bool operator==(const Transaction &lhs, const Transaction &rhs) {
    return
        amount(lhs) == amount(rhs) &&
        lhs.label == rhs.label &&
        lhs.date == rhs.date;
}

void TransactionRecord::add(const Transaction &t) {
    transactions.push_back(t);
}

std::vector<Transaction> TransactionRecord::findByAmount(int amount_) {
    std::vector<Transaction> found;
    std::copy_if(
        transactions.begin(),
        transactions.end(),
        std::back_inserter(found),
        [=](auto t) { return amount(t) == amount_; }
    );
    return found;
}

int TransactionRecord::netIncome() {
    return transactions.size() ? transactions.front().amount : 0;
}
}