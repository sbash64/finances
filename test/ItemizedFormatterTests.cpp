#include <finances/Transaction.hpp>

namespace finances {
class ItemizedFormatter {
public:
    std::string format(const Transactions &) {
        return "-50 hyvee 10/5/19";
    }
};
}

#include <catch2/catch.hpp>

namespace finances { namespace {
class ItemizedFormatterTests {
    ItemizedFormatter formatter;
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, std::move(label), std::move(date)};
    }

    std::string format(const Transactions &t) {
        return formatter.format(t);
    }
};

#define ASSERT_FORMAT_ONE(a, b, c, d)\
    CHECK(d == format(Transactions{transaction(a, b, c)}))

TEST_CASE_METHOD(ItemizedFormatterTests, "tbd") {
    ASSERT_FORMAT_ONE(
        -5000, "hyvee", "10/5/19",
        "-50 hyvee 10/5/19"
    );
}
}}
