#ifndef TEST_TESTING_UTILITY_HPP_
#define TEST_TESTING_UTILITY_HPP_

#include <finances/Transaction.hpp>
#include <catch2/catch.hpp>

#define ASSERT_EQUAL(a, b) CHECK(a == b)

namespace finances {
inline Transaction transaction(int amount, std::string label, std::string date) {
    return {amount, std::move(label), std::move(date)};
}
}

#endif
