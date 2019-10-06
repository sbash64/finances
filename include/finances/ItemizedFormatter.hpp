#ifndef FINANCES_ITEMIZEDFORMATTER_HPP_
#define FINANCES_ITEMIZEDFORMATTER_HPP_

#include <finances/Transaction.hpp>

namespace finances {
class ItemizedFormatter {
public:
    std::string format(const Transactions &);
};
}

#endif
