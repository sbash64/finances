#include "ItemizedFormatterTests.hpp"
#include "testing-utility.hpp"
#include <finances/ItemizedFormatter.hpp>
#include <testcpplite/testcpplite.hpp>
#include <functional>

namespace finances {
namespace {
auto format(ItemizedFormatter &formatter, const Transactions &t)
    -> std::string {
    return formatter.format(t);
}

void testItemizedFormatter(const std::function<void(ItemizedFormatter &)> &f) {
    ItemizedFormatter formatter;
    f(formatter);
}
}

void itemizedFormatterFormatsOneTransaction(testcpplite::TestResult &result) {
    testItemizedFormatter([&](ItemizedFormatter &formatter) {
        assertEqual(result, "-50.00 hyvee 10/5/19",
            format(formatter, oneTransaction(-5000, "hyvee", "10/5/19")));
    });
}

void itemizedFormatterFormatsTwoTransactions(testcpplite::TestResult &result) {
    testItemizedFormatter([&](ItemizedFormatter &formatter) {
        assertEqual(result,
            "-50.00 hyvee 10/5/19\n"
            "-9.79 chipotle 10/4/19",
            format(formatter,
                twoTransactions(
                    -5000, "hyvee", "10/5/19", -979, "chipotle", "10/4/19")));
    });
}

void itemizedFormatterFormatsNetIncome(testcpplite::TestResult &result) {
    testItemizedFormatter([&](ItemizedFormatter &formatter) {
        NetIncome netIncome{};
        netIncome.cents = -979;
        assertEqual(result, "Net Income: -9.79", formatter.format(netIncome));
    });
}
}
