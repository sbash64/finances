#ifndef FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_
#define FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_

#include "Transaction.hpp"
#include "Presenter.hpp"

namespace finances {
class TransactionRecord : public Model {
public:
    void add(const Transaction &) override;
    void remove(const Transaction &);
    Transactions findByAmount(int);
    int netIncome() override;
    Transactions transactions() override;
private:
    Transactions transactions_;
};
}

#endif
