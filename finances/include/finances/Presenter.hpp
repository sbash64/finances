#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "TransactionRecord.hpp"
#include "View.hpp"

namespace finances {
class Presenter : TransactionRecord::EventListener {
  public:
    Presenter(View &);
    void verified(const Transaction &) override;
    void added(const Transaction &) override;

  private:
    View &view;
};
}

#endif
