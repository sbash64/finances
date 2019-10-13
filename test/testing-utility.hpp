#ifndef TEST_TESTING_UTILITY_HPP_
#define TEST_TESTING_UTILITY_HPP_

#include <finances/Transaction.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <utility>

#define ASSERT_EQUAL(a, b) CHECK(a == b)

namespace finances {
inline Transaction transaction(
    int amount, std::string label, std::string date
) {
    return {amount, std::move(label), std::move(date)};
}

inline Transactions oneTransaction(
    int amount,
    std::string label,
    std::string date
) {
    return { transaction(amount, std::move(label), std::move(date)) };
}

inline Transactions twoTransactions(
    int amount1, std::string label1, std::string date1,
    int amount2, std::string label2, std::string date2
) {
    return {
        transaction(amount1, std::move(label1), std::move(date1)),
        transaction(amount2, std::move(label2), std::move(date2))
    };
}

inline Transactions threeTransactions(
    int amount1, std::string label1, std::string date1,
    int amount2, std::string label2, std::string date2,
    int amount3, std::string label3, std::string date3
) {
    return {
        transaction(amount1, std::move(label1), std::move(date1)),
        transaction(amount2, std::move(label2), std::move(date2)),
        transaction(amount3, std::move(label3), std::move(date3))
    };
}
}

#endif
