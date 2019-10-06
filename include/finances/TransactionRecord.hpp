#ifndef FINANCES_TRANSACTIONRECORD_HPP_
#define FINANCES_TRANSACTIONRECORD_HPP_

#include "Transaction.hpp"

namespace finances {
class TransactionRecord {
public:
    void add(const Transaction &);
    void remove(const Transaction &);
    Transactions findByAmount(int);
    int netIncome();
    Transactions getAll();
private:
    Transactions transactions;
};
}

#endif
