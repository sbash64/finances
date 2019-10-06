#ifndef FINANCES_TRANSACTIONRECORD_HPP_
#define FINANCES_TRANSACTIONRECORD_HPP_

#include <string>
#include <vector>
#include <algorithm>

namespace finances {
struct Transaction {
    int amount;
    std::string label;
    std::string date;
};

int amount(const Transaction &);
bool operator==(const Transaction &, const Transaction &);

class TransactionRecord {
    std::vector<Transaction> transactions;
public:
    void add(const Transaction &);
    std::vector<Transaction> findByAmount(int);
};
}

#endif
