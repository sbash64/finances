#ifndef FINANCES_INCLUDE_FINANCES_ITEMIZEDFORMATTER_HPP_
#define FINANCES_INCLUDE_FINANCES_ITEMIZEDFORMATTER_HPP_

#include "Transaction.hpp"
#include "FormattedWriter.hpp"

namespace sbash64::finances {
class ItemizedFormatter : public Formatter {
  public:
    auto format(const Transactions &) -> std::string override;
    auto format(const NetIncome &) -> std::string override;
};
}

#endif
