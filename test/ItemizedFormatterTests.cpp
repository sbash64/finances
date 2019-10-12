#include "testing-utility.hpp"
#include <finances/ItemizedFormatter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class ItemizedFormatterTests {
    ItemizedFormatter formatter;
protected:
    std::string formatTransactions(const Transactions &t) {
        return formatter.formatTransactions(t);
    }

    std::string formatNetIncome(int x) {
        return formatter.formatNetIncome(x);
    }
};

#define ASSERT_FORMAT_ONE_TRANSACTION(a, b, c, d)\
    ASSERT_EQUAL(d, formatTransactions(oneTransaction(a, b, c)))

#define ASSERT_FORMAT_TWO_TRANSACTIONS(a, b, c, d, e, f, g)\
    ASSERT_EQUAL(g, formatTransactions(twoTransactions(a, b, c, d, e, f)))

#define ASSERT_FORMAT_NET_INCOME(a, b)\
    ASSERT_EQUAL(b, formatNetIncome(a))

TEST_CASE_METHOD(ItemizedFormatterTests, "formatOneTransaction") {
    ASSERT_FORMAT_ONE_TRANSACTION(
        -5000, "hyvee", "10/5/19",
        "-50.00 hyvee 10/5/19"
    );
}

TEST_CASE_METHOD(ItemizedFormatterTests, "formatTwoTransactions") {
    ASSERT_FORMAT_TWO_TRANSACTIONS(
        -5000, "hyvee", "10/5/19",
        -979, "chipotle", "10/4/19",
        "-50.00 hyvee 10/5/19\n"
        "-9.79 chipotle 10/4/19"
    );
}

TEST_CASE_METHOD(ItemizedFormatterTests, "formatNetIncome") {
    ASSERT_FORMAT_NET_INCOME(
        -979,
        "Net Income: -9.79"
    );
}
}}
