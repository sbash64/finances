#include "testing-utility.hpp"
#include <finances/TransactionRecord.hpp>
#include <catch2/catch.hpp>

namespace finances {
namespace {
auto none() -> Transactions { return {}; }

class TransactionRecordTests {
  protected:
    void add(int amount, std::string label, std::string date) {
        record.add(transaction(amount, std::move(label), std::move(date)));
    }

    void verify(int amount) { record.verify(amount); }

    void remove(int amount, std::string label, std::string date) {
        record.remove(transaction(amount, std::move(label), std::move(date)));
    }

    auto netIncome() -> int { return record.netIncome(); }

    auto verifiedTransactions() -> Transactions {
        return record.verifiedTransactions();
    }

    auto unverifiedTransactions() -> Transactions {
        return record.unverifiedTransactions();
    }

    auto all() -> Transactions { return record.transactions(); }

    auto didVerify() -> bool { return record.didVerify(); }

    auto didNotVerify() -> bool { return !didVerify(); }

  private:
    TransactionRecord record;
};

#define ASSERT_TRANSACTIONS(a) ASSERT_EQUAL(a, all())

#define ASSERT_NO_TRANSACTIONS() ASSERT_TRANSACTIONS(none())

#define ASSERT_ONE_TRANSACTION(a, b, c)                                        \
    ASSERT_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_TWO_TRANSACTIONS(a, b, c, d, e, f)                              \
    ASSERT_TRANSACTIONS(twoTransactions(a, b, c, d, e, f))

#define ASSERT_THREE_TRANSACTIONS(a, b, c, d, e, f, g, h, i)                   \
    ASSERT_TRANSACTIONS(threeTransactions(a, b, c, d, e, f, g, h, i))

#define ASSERT_VERIFIED_TRANSACTIONS(expected)                                 \
    ASSERT_EQUAL(expected, verifiedTransactions())

#define ASSERT_ONE_VERIFIED_TRANSACTION(a, b, c)                               \
    ASSERT_VERIFIED_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_UNVERIFIED_TRANSACTIONS(expected)                               \
    ASSERT_EQUAL(expected, unverifiedTransactions())

#define ASSERT_ONE_UNVERIFIED_TRANSACTION(a, b, c)                             \
    ASSERT_UNVERIFIED_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_TWO_VERIFIED_TRANSACTIONS(a, b, c, d, e, f)                     \
    ASSERT_VERIFIED_TRANSACTIONS(twoTransactions(a, b, c, d, e, f))

#define ASSERT_NET_INCOME(expected) ASSERT_EQUAL(expected, netIncome())

#define ASSERT_NO_VERIFIED_TRANSACTIONS() ASSERT_VERIFIED_TRANSACTIONS(none())

#define ASSERT_NO_UNVERIFIED_TRANSACTIONS()                                    \
    ASSERT_UNVERIFIED_TRANSACTIONS(none())

#define ASSERT_EXISTS_EXACTLY_ONE_VERIFIED_TRANSACTION()                       \
    ASSERT_EQUAL(1, verifiedTransactions().size())

#define ASSERT_DID_NOT_VERIFY() ASSERT_TRUE(didNotVerify())

#define ASSERT_DID_VERIFY() ASSERT_TRUE(didVerify())

#define TRANSACTION_RECORD_TEST(a) TEST_CASE_METHOD(TransactionRecordTests, a)

// clang-format off

TRANSACTION_RECORD_TEST("noneOnConstruction") {
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneAdded") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_ONE_TRANSACTION(-5000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("twoAdded") {
    add(-1000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_TWO_TRANSACTIONS(
        -1000, "hyvee", "10/5/19",
        -1000, "chipotle", "10/5/19"
    );
}

TRANSACTION_RECORD_TEST("removesOne") {
    add(-5000, "hyvee", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("threeAdded") {
    add(-2000, "hyvee", "10/5/19");
    add(-3000, "walmart", "10/4/19");
    add(-1000, "chipotle", "10/6/19");
    ASSERT_THREE_TRANSACTIONS(
        -2000, "hyvee", "10/5/19",
        -3000, "walmart", "10/4/19",
        -1000, "chipotle", "10/6/19"
    );
}

TRANSACTION_RECORD_TEST("removesOneFromNone") {
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("removeOneFromTwo") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_ONE_TRANSACTION(-1000, "chipotle", "10/5/19");
}

TRANSACTION_RECORD_TEST("removeOneNotFoundFromTwo") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    remove(-4999, "hyvee", "10/5/19");
    ASSERT_TWO_TRANSACTIONS(
        -5000, "hyvee", "10/5/19",
        -1000, "chipotle", "10/5/19"
    );
}

TRANSACTION_RECORD_TEST("netIncomeZeroOnConstruction") {
    ASSERT_NET_INCOME(0);
}

TRANSACTION_RECORD_TEST("netIncomeFromOne") {
    add(-1000, "hyvee", "10/5/19");
    ASSERT_NET_INCOME(-1000);
}

TRANSACTION_RECORD_TEST("netIncomeFromTwo") {
    add(-6132, "hyvee", "10/5/19");
    add(-1254, "chipotle", "10/5/19");
    ASSERT_NET_INCOME(-7386);
}

TRANSACTION_RECORD_TEST("noVerifiedOnConstruction") {
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneNotVerified") {
    add(-2000, "hyvee", "10/5/19");
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneVerified") {
    add(-2000, "hyvee", "10/5/19");
    verify(-2000);
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("oneOfTwoVerified") {
    add(-2000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/6/19");
    verify(-2000);
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("twoOfThreeVerified") {
    add(-2000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/6/19");
    add(-3000, "barnes noble", "10/4/19");
    verify(-2000);
    verify(-3000);
    ASSERT_TWO_VERIFIED_TRANSACTIONS(
        -2000, "hyvee", "10/5/19",
        -3000, "barnes noble", "10/4/19"
    );
}

TRANSACTION_RECORD_TEST("oneFromNoneVerified") {
    verify(-3000);
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("noneVerifiedDidNotVerify") {
    add(-2000, "hyvee", "10/5/19");
    verify(-1000);
    ASSERT_DID_NOT_VERIFY();
}

TRANSACTION_RECORD_TEST("oneVerifiedDidVerify") {
    add(-2000, "hyvee", "10/5/19");
    verify(-2000);
    ASSERT_DID_VERIFY();
}

TRANSACTION_RECORD_TEST("oneVerifiedBeforeNoneDidNotVerify") {
    add(-2000, "hyvee", "10/5/19");
    verify(-2000);
    verify(-1000);
    ASSERT_DID_NOT_VERIFY();
}

TRANSACTION_RECORD_TEST("noUnverifiedOnConstruction") {
    ASSERT_NO_UNVERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneUnverified") {
    add(-1000, "hyvee", "10/1/19");
    ASSERT_ONE_UNVERIFIED_TRANSACTION(-1000, "hyvee", "10/1/19");
}

TRANSACTION_RECORD_TEST("oneOfTwoUnverified") {
    add(-2000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/6/19");
    verify(-2000);
    ASSERT_ONE_UNVERIFIED_TRANSACTION(-1000, "chipotle", "10/6/19");
}

TRANSACTION_RECORD_TEST("verifyBothOfSameAmount") {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    verify(-2000);
    ASSERT_TWO_VERIFIED_TRANSACTIONS(
        -2000, "hyvee", "10/5/19",
        -2000, "chipotle", "10/6/19"
    );
}

TRANSACTION_RECORD_TEST("onlyVerifiesOneOfTwoSameAmounts") {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    ASSERT_EXISTS_EXACTLY_ONE_VERIFIED_TRANSACTION();
}

TRANSACTION_RECORD_TEST("removeFirstAmongOneOfTwoVerifiesOther") {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    remove(-2000, "hyvee", "10/5/19");
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "chipotle", "10/6/19");
}

TRANSACTION_RECORD_TEST("removeSecondAmongOneOfTwoVerifiesOther") {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    remove(-2000, "chipotle", "10/6/19");
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("removeOneUnverifiedDoesNotVerifyOther") {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    remove(-2000, "chipotle", "10/6/19");
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

// clang-format on

}
}
