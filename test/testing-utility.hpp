#ifndef TEST_TESTING_UTILITY_HPP_
#define TEST_TESTING_UTILITY_HPP_

#include <finances/Transaction.hpp>
#include <testcpplite/testcpplite.hpp>
#include <catch2/catch.hpp>
#include <string>
#include <utility>

#define ASSERT_EQUAL(a, b) CHECK(a == b)
#define ASSERT_TRUE(a) CHECK(a)

namespace finances {
inline auto transaction(int amount, std::string label, std::string date)
    -> Transaction {
    return {amount, std::move(label), std::move(date)};
}

inline auto oneTransaction(int amount, std::string label, std::string date)
    -> Transactions {
    return {transaction(amount, std::move(label), std::move(date))};
}

inline auto twoTransactions(int amount1, std::string label1, std::string date1,
    int amount2, std::string label2, std::string date2) -> Transactions {
    return {transaction(amount1, std::move(label1), std::move(date1)),
        transaction(amount2, std::move(label2), std::move(date2))};
}

inline auto threeTransactions(int amount1, std::string label1,
    std::string date1, int amount2, std::string label2, std::string date2,
    int amount3, std::string label3, std::string date3) -> Transactions {
    return {transaction(amount1, std::move(label1), std::move(date1)),
        transaction(amount2, std::move(label2), std::move(date2)),
        transaction(amount3, std::move(label3), std::move(date3))};
}

inline void assertEqual(testcpplite::TestResult &result, const Transaction &expected,
    const Transaction &actual) {
    assertEqual(result, expected.amount, actual.amount);
    assertEqual(result, expected.date, actual.date);
    assertEqual(result, expected.label, actual.label);
}
}

#endif
