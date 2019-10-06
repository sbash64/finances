#include <finances/Transaction.hpp>

namespace finances {
std::string string(int x) {
    return std::to_string(x);
}

class ItemizedFormatter {
public:
    std::string format(const Transactions &transactions) {
        std::string formatted;
        bool first = true;
        for (auto transaction : transactions) {
            if (!first)
                formatted += '\n';
            auto amountBeforeDecimal = amount(transaction) / 100;
            auto amountAfterDecimal =
                std::abs(amount(transaction) - amountBeforeDecimal * 100);
            auto leadingZero =  "";
            if (amountAfterDecimal < 10)
                leadingZero = "0";
            auto beforeDecimal = string(amountBeforeDecimal);
            auto afterDecimal = leadingZero + string(amountAfterDecimal);
            formatted +=
                beforeDecimal + "." + afterDecimal + " " +
                transaction.label + " " +
                transaction.date;
            first = false;
        }
        return formatted;
    }
};
}

#include "testing-utility.hpp"
#include <catch2/catch.hpp>

namespace finances { namespace {
class ItemizedFormatterTests {
    ItemizedFormatter formatter;
protected:
    std::string format(const Transactions &t) {
        return formatter.format(t);
    }
};

#define ASSERT_FORMAT_ONE(a, b, c, d)\
    CHECK(d == format(Transactions{transaction(a, b, c)}))
#define ASSERT_FORMAT_TWO(a, b, c, d, e, f, g)\
    CHECK(g == format(Transactions{\
        transaction(a, b, c), \
        transaction(d, e, f)\
    }))

TEST_CASE_METHOD(ItemizedFormatterTests, "formatOne") {
    ASSERT_FORMAT_ONE(
        -5000, "hyvee", "10/5/19",
        "-50.00 hyvee 10/5/19"
    );
}

TEST_CASE_METHOD(ItemizedFormatterTests, "formatTwo") {
    ASSERT_FORMAT_TWO(
        -5000, "hyvee", "10/5/19",
        -979, "chipotle", "10/4/19",
        "-50.00 hyvee 10/5/19\n"
        "-9.79 chipotle 10/4/19"
    );
}
}}
