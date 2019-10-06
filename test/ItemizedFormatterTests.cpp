#include <finances/Transaction.hpp>

namespace finances {
class ItemizedFormatter {
public:
    std::string format(const Transactions &t) {
        auto first = t.front();
        auto amountBeforeDecimal = first.amount / 100;
        auto amountAfterDecimal = first.amount - amountBeforeDecimal * 100;
        auto leadingZero =  "";
        if (amountAfterDecimal < 10)
            leadingZero = "0";
        auto beforeDecimal = std::to_string(amountBeforeDecimal);
        auto afterDecimal = leadingZero + std::to_string(amountAfterDecimal);
        return beforeDecimal + "." + afterDecimal + " " + first.label + " " + first.date;
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

TEST_CASE_METHOD(ItemizedFormatterTests, "tbd") {
    ASSERT_FORMAT_ONE(
        -5000, "hyvee", "10/5/19",
        "-50.00 hyvee 10/5/19"
    );
}
}}
