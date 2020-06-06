#ifndef FINANCES_INCLUDE_FINANCES_VIEW_HPP_
#define FINANCES_INCLUDE_FINANCES_VIEW_HPP_

#include "Transaction.hpp"

namespace finances {
class View {
  public:
    virtual ~View() = default;
    virtual void show(const Transactions &) = 0;
    virtual void show(const NetIncome &) = 0;
};
}

#endif
