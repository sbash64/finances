#include <finances/TransactionRecord.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class TransactionRecordTests {
    TransactionRecord record;
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, std::move(label), std::move(date)};
    }

    Transactions onlyOne(
        int amount,
        std::string label,
        std::string date
    ) {
        return { transaction(amount, std::move(label), std::move(date)) };
    }

    void add(int amount, std::string label, std::string date) {
        record.add(transaction(amount, std::move(label), std::move(date)));
    }

    void remove(int amount, std::string label, std::string date) {
        record.remove(transaction(amount, std::move(label), std::move(date)));
    }

    Transactions findByAmount(int amount) {
        return record.findByAmount(amount);
    }

    Transactions none() {
        return {};
    }

    int netIncome() {
        return record.netIncome();
    }

    Transactions getAll() {
        return record.getAll();
    }
};

#define ASSERT_EQUAL(a, b) CHECK(a == b)
#define ASSERT_TRANSACTIONS_BY_AMOUNT(a, b) ASSERT_EQUAL(a, findByAmount(b))
#define ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(a, b, c, d)\
    ASSERT_TRANSACTIONS_BY_AMOUNT(onlyOne(a, b, c), d)
#define ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(a)\
    ASSERT_TRANSACTIONS_BY_AMOUNT(none(), a)
#define ASSERT_TWO_TRANSACTIONS_FOR_AMOUNT(a, b, c, d, e, f, g)\
    CHECK(\
        Transactions{\
            transaction(a, b, c), \
            transaction(d, e, f)\
        } == findByAmount(g)\
    )
#define ASSERT_NET_INCOME(a) ASSERT_EQUAL(a, netIncome())
#define ASSERT_THREE_TRANSACTIONS(a, b, c, d, e, f, g, h, i)\
    CHECK(\
        Transactions{\
            transaction(a, b, c), \
            transaction(d, e, f), \
            transaction(g, h, i)\
        } == getAll()\
    )

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountNone") {
    ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(0);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountNoneFound") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(0);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountOneFoundOnlyOne") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(
        -5000, "hyvee", "10/5/19",
        -5000
    );
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountOneFound") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(
        -5000, "hyvee", "10/5/19",
        -5000
    );
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountBothFound") {
    add(-1000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_TWO_TRANSACTIONS_FOR_AMOUNT(
        -1000, "hyvee", "10/5/19",
        -1000, "chipotle", "10/5/19",
        -1000
    );
}

TEST_CASE_METHOD(TransactionRecordTests, "netIncomeNoTransactions") {
    ASSERT_NET_INCOME(0);
}

TEST_CASE_METHOD(TransactionRecordTests, "netIncomeOneTransaction") {
    add(-1000, "hyvee", "10/5/19");
    ASSERT_NET_INCOME(-1000);
}

TEST_CASE_METHOD(TransactionRecordTests, "netIncomeTwoTransactions") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_NET_INCOME(-6000);
}

TEST_CASE_METHOD(TransactionRecordTests, "removeOnlyTransaction") {
    add(-5000, "hyvee", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(-5000);
}

TEST_CASE_METHOD(TransactionRecordTests, "removeNonExistingTransaction") {
    remove(-5000, "hyvee", "10/5/19");
}

TEST_CASE_METHOD(TransactionRecordTests, "removeATransaction") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    remove(-5000, "hyvee", "10/5/19");
    ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(
        -1000, "chipotle", "10/5/19",
        -1000
    );
}

TEST_CASE_METHOD(TransactionRecordTests, "getAll") {
    add(-2000, "hyvee", "10/5/19");
    add(-3000, "walmart", "10/4/19");
    add(-1000, "chipotle", "10/6/19");
    ASSERT_THREE_TRANSACTIONS(
        -2000, "hyvee", "10/5/19",
        -3000, "walmart", "10/4/19",
        -1000, "chipotle", "10/6/19"
    );
}
}}
