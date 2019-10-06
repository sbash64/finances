#include "testing-utility.hpp"
#include <finances/ItemizedFormatter.hpp>
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
