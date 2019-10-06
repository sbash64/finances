#ifndef FINANCES_ITEMIZEDFORMATTER_HPP_
#define FINANCES_ITEMIZEDFORMATTER_HPP_

#include "Transaction.hpp"
#include "FormattedWriter.hpp"

namespace finances {
class ItemizedFormatter : public Formatter {
public:
    std::string format(const Transactions &) override;
};
}

#endif
