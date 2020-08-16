#ifndef FINANCES_INCLUDE_FINANCES_MODEL_HPP_
#define FINANCES_INCLUDE_FINANCES_MODEL_HPP_

#include "Transaction.hpp"

namespace sbash64::finances {
class Model {
  public:
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual void remove(const Transaction &) = 0;
    virtual void verify(Amount) = 0;
    virtual auto transactions() -> Transactions = 0;
    virtual auto verifiedTransactions() -> Transactions = 0;
    virtual auto unverifiedTransactions() -> Transactions = 0;
    virtual auto netIncome() -> NetIncome = 0;
};
}

#endif
