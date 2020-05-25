#ifndef FINANCES_INCLUDE_FINANCES_MODEL_HPP_
#define FINANCES_INCLUDE_FINANCES_MODEL_HPP_

#include "Transaction.hpp"

namespace finances {
class Model {
  public:
    class EventListener {
      public:
        virtual ~EventListener() = default;
        virtual void verified(const Transaction &) = 0;
        virtual void added(const Transaction &) = 0;
    };
    virtual ~Model() = default;
    virtual void add(const Transaction &) = 0;
    virtual void remove(const Transaction &) = 0;
    virtual void verify(int amount) = 0;
    virtual auto transactions() -> Transactions = 0;
    virtual auto verifiedTransactions() -> Transactions = 0;
    virtual auto unverifiedTransactions() -> Transactions = 0;
    virtual auto netIncome() -> int = 0;
    virtual void subscribe(EventListener *) = 0;
};
}

#endif
