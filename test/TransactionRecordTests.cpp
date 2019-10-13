#include "testing-utility.hpp"
#include <finances/TransactionRecord.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class TransactionRecordTests {
protected:
    void add(int amount, std::string label, std::string date) {
        record.add(transaction(amount, std::move(label), std::move(date)));
    }

    void verify(int amount) {
        record.verify(amount);
    }

    void remove(int amount, std::string label, std::string date) {
        record.remove(transaction(amount, std::move(label), std::move(date)));
    }

    int netIncome() {
        return record.netIncome();
    }

    Transactions verifiedTransactions() {
        return record.verifiedTransactions();
    }

    Transactions unverifiedTransactions() {
        return record.unverifiedTransactions();
    }

    Transactions all() {
        return record.transactions();
    }

    Transactions none() {
        return {};
    }
private:
    TransactionRecord record;
};

#define ASSERT_TRANSACTIONS(a)\
    ASSERT_EQUAL(a, all())

#define ASSERT_NO_TRANSACTIONS()\
    ASSERT_TRANSACTIONS(none())

#define ASSERT_ONE_TRANSACTION(a, b, c)\
    ASSERT_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_TWO_TRANSACTIONS(a, b, c, d, e, f)\
    ASSERT_TRANSACTIONS(twoTransactions(a, b, c, d, e, f))

#define ASSERT_THREE_TRANSACTIONS(a, b, c, d, e, f, g, h, i)\
    ASSERT_TRANSACTIONS(threeTransactions(a, b, c, d, e, f, g, h, i))

#define ASSERT_VERIFIED_TRANSACTIONS(expected)\
    ASSERT_EQUAL(expected, verifiedTransactions())

#define ASSERT_ONE_VERIFIED_TRANSACTION(a, b, c)\
    ASSERT_VERIFIED_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_UNVERIFIED_TRANSACTIONS(expected)\
    ASSERT_EQUAL(expected, unverifiedTransactions())

#define ASSERT_ONE_UNVERIFIED_TRANSACTION(a, b, c)\
    ASSERT_UNVERIFIED_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_TWO_VERIFIED_TRANSACTIONS(a, b, c, d, e, f)\
    ASSERT_VERIFIED_TRANSACTIONS(twoTransactions(a, b, c, d, e, f))

#define ASSERT_NET_INCOME(expected)\
    ASSERT_EQUAL(expected, netIncome())

#define ASSERT_NO_VERIFIED_TRANSACTIONS()\
    ASSERT_VERIFIED_TRANSACTIONS(none())

#define ASSERT_NO_UNVERIFIED_TRANSACTIONS()\
    ASSERT_UNVERIFIED_TRANSACTIONS(none())

#define ASSERT_EXISTS_EXACTLY_ONE_VERIFIED_TRANSACTION()\
    ASSERT_EQUAL(1, verifiedTransactions().size())

#define TRANSACTION_RECORD_TEST(a)\
    TEST_CASE_METHOD(TransactionRecordTests, a)

TRANSACTION_RECORD_TEST("noTransactionsOnConstruction") {
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneTransactionAdded") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_ONE_TRANSACTION(-5000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("twoTransactionsAdded") {
    add(-1000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_TWO_TRANSACTIONS(
        -1000, "hyvee", "10/5/19",
        -1000, "chipotle", "10/5/19"
    );
}

TRANSACTION_RECORD_TEST("removesOnlyTransaction") {
    add(-5000, "hyvee", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("threeTransactions") {
    add(-2000, "hyvee", "10/5/19");
    add(-3000, "walmart", "10/4/19");
    add(-1000, "chipotle", "10/6/19");
    ASSERT_THREE_TRANSACTIONS(
        -2000, "hyvee", "10/5/19",
        -3000, "walmart", "10/4/19",
        -1000, "chipotle", "10/6/19"
    );
}

TRANSACTION_RECORD_TEST("removeTransactionNoneToBeginWith") {
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("removeOneTransactionFromTwo") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_ONE_TRANSACTION(-1000, "chipotle", "10/5/19");
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "removeOneTransactionNotFoundFromTwo"
) {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    remove(-4999, "hyvee", "10/5/19");
    ASSERT_TWO_TRANSACTIONS(
        -5000, "hyvee", "10/5/19",
        -1000, "chipotle", "10/5/19"
    );
}

TRANSACTION_RECORD_TEST("netIncomeNoTransactions") {
    ASSERT_NET_INCOME(0);
}

TRANSACTION_RECORD_TEST("netIncomeOneTransaction") {
    add(-1000, "hyvee", "10/5/19");
    ASSERT_NET_INCOME(-1000);
}

TRANSACTION_RECORD_TEST("netIncomeTwoTransactions") {
    add(-6132, "hyvee", "10/5/19");
    add(-1254, "chipotle", "10/5/19");
    ASSERT_NET_INCOME(-7386);
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "noVerifiedTransactionsOnConstruction"
) {
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("onlyTransactionNotVerified") {
    add(-2000, "hyvee", "10/5/19");
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("oneOfOneVerifiedTransactions") {
    add(-2000, "hyvee", "10/5/19");
    verify(-2000);
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("oneOfTwoVerifiedTransactions") {
    add(-2000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/6/19");
    verify(-2000);
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TRANSACTION_RECORD_TEST("twoOfThreeVerifiedTransactions") {
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

TRANSACTION_RECORD_TEST("noneVerifiedDespiteEffort") {
    verify(-3000);
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "noUnverifiedTransactionsOnConstruction"
) {
    ASSERT_NO_UNVERIFIED_TRANSACTIONS();
}

TRANSACTION_RECORD_TEST("onlyTransactionUnverified") {
    add(-1000, "hyvee", "10/1/19");
    ASSERT_ONE_UNVERIFIED_TRANSACTION(-1000, "hyvee", "10/1/19");
}

TRANSACTION_RECORD_TEST("oneOfTwoUnverifiedTransactions") {
    add(-2000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/6/19");
    verify(-2000);
    ASSERT_ONE_UNVERIFIED_TRANSACTION(-1000, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "canVerifyBothTransactionsOfSameAmount"
) {
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

TEST_CASE_METHOD(
    TransactionRecordTests,
    "removeFirstAmongOneOfTwoPossibleVerifiedTransactionsVerifiesOther"
) {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    remove(-2000, "hyvee", "10/5/19");
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "removeSecondAmongOneOfTwoPossibleVerifiedTransactionsVerifiesOther"
) {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    verify(-2000);
    remove(-2000, "chipotle", "10/6/19");
    ASSERT_ONE_VERIFIED_TRANSACTION(-2000, "hyvee", "10/5/19");
}

TEST_CASE_METHOD(
    TransactionRecordTests,
    "removeOneNotVerifiedDoesNotVerifyOther"
) {
    add(-2000, "hyvee", "10/5/19");
    add(-2000, "chipotle", "10/6/19");
    remove(-2000, "chipotle", "10/6/19");
    ASSERT_NO_VERIFIED_TRANSACTIONS();
}
}}
