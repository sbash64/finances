#ifndef FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_
#define FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_

#include "Transaction.hpp"
#include "Presenter.hpp"
#include <vector>

namespace finances {
struct VerifiableTransaction {
    Transaction transaction;
    bool verified;
};

using VerifiableTransactions = std::vector<VerifiableTransaction>;

class TransactionRecord : public Model {
public:
    void add(const Transaction &) override;
    void remove(const Transaction &) override;
    int netIncome() override;
    Transactions transactions() override;
    void verify(int) override;
    Transactions verifiedTransactions() override;
    Transactions unverifiedTransactions() override;
private:
    VerifiableTransactions verifiableTransactions;
};
}

#endif
