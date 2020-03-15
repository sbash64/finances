#ifndef FINANCES_INCLUDE_FINANCES_ITEMIZEDFORMATTER_HPP_
#define FINANCES_INCLUDE_FINANCES_ITEMIZEDFORMATTER_HPP_

#include "Transaction.hpp"
#include "FormattedWriter.hpp"

namespace finances {
class ItemizedFormatter : public Formatter {
  public:
    auto format(const Transactions &) -> std::string override;
    auto formatNetIncome(int) -> std::string override;
};
}

#endif
