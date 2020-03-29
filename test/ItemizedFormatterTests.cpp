#include "testing-utility.hpp"
#include <finances/ItemizedFormatter.hpp>
#include <catch2/catch.hpp>

namespace finances {
namespace {
class ItemizedFormatterTests {
  protected:
    auto format(const Transactions &t) -> std::string {
        return formatter.format(t);
    }

    auto formatNetIncome(int x) -> std::string {
        return formatter.formatNetIncome(x);
    }

  private:
    ItemizedFormatter formatter;
};

#define ASSERT_FORMAT_ONE_TRANSACTION(a, b, c, d)                              \
    ASSERT_EQUAL(d, format(oneTransaction(a, b, c)))

#define ASSERT_FORMAT_TWO_TRANSACTIONS(a, b, c, d, e, f, g)                    \
    ASSERT_EQUAL(g, format(twoTransactions(a, b, c, d, e, f)))

#define ASSERT_FORMAT_NET_INCOME(a, b) ASSERT_EQUAL(b, formatNetIncome(a))

#define ITEMIZED_FORMATTER_TEST(a) TEST_CASE_METHOD(ItemizedFormatterTests, a)

// clang-format off

ITEMIZED_FORMATTER_TEST("formatOneTransaction") {
    ASSERT_FORMAT_ONE_TRANSACTION(
        -5000, "hyvee", "10/5/19",
        "-50.00 hyvee 10/5/19"
    );
}

ITEMIZED_FORMATTER_TEST("formatTwoTransactions") {
    ASSERT_FORMAT_TWO_TRANSACTIONS(
        -5000, "hyvee", "10/5/19",
        -979, "chipotle", "10/4/19",
        "-50.00 hyvee 10/5/19\n"
        "-9.79 chipotle 10/4/19"
    );
}

ITEMIZED_FORMATTER_TEST("formatNetIncome") {
    ASSERT_FORMAT_NET_INCOME(-979, "Net Income: -9.79");
}

// clang-format on

}
}
