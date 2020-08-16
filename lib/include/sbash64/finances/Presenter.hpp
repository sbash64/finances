#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "TransactionRecord.hpp"
#include "View.hpp"

namespace sbash64::finances {
class Presenter : public TransactionRecord::EventListener {
  public:
    Presenter(View &);
    void verified(const Transaction &) override;
    void added(const Transaction &) override;
    void print(const Transactions &);
    void print(NetIncome);

  private:
    View &view;
};
}

#endif
