#ifndef TEST_TESTING_UTILITY_HPP_
#define TEST_TESTING_UTILITY_HPP_

#include <finances/Transaction.hpp>

namespace finances {
inline Transaction transaction(int amount, std::string label, std::string date) {
    return {amount, std::move(label), std::move(date)};
}
}

#endif
