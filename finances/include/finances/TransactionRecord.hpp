#ifndef FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_
#define FINANCES_INCLUDE_FINANCES_TRANSACTIONRECORD_HPP_

#include "Transaction.hpp"
#include "CommandResponder.hpp"
#include <vector>

namespace finances {
struct VerifiableTransaction : Transaction {
    bool verified{};
};

using VerifiableTransactions = std::vector<VerifiableTransaction>;

class TransactionRecord : public Model {
  public:
    class EventListener {
      public:
        virtual ~EventListener() = default;
        virtual void verified(const Transaction &) = 0;
        virtual void added(const Transaction &) = 0;
    };
    explicit TransactionRecord(EventListener &);
    void add(const Transaction &) override;
    void remove(const Transaction &) override;
    auto netIncome() -> NetIncome override;
    auto transactions() -> Transactions override;
    void verify(const Amount &) override;
    auto verifiedTransactions() -> Transactions override;
    auto unverifiedTransactions() -> Transactions override;

  private:
    VerifiableTransactions verifiableTransactions;
    EventListener &listener;
};
}

#endif
