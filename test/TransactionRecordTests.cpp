#include <string>
#include <vector>
#include <algorithm>

namespace finances {
struct Transaction {
    int amount;
    std::string label;
    std::string date;
};

int amount(const Transaction &t) {
    return t.amount;
}

bool operator==(const Transaction &lhs, const Transaction &rhs) {
    return
        amount(lhs) == amount(rhs) &&
        lhs.label == rhs.label &&
        lhs.date == rhs.date;
}

class TransactionRecord {
    std::vector<Transaction> transactions;
public:
    void add(Transaction t) {
        transactions.push_back(t);
    }

    std::vector<Transaction> findByAmount(int amount_) {
        std::vector<Transaction> found;
        std::copy_if(
            transactions.begin(),
            transactions.end(),
            std::back_inserter(found),
            [=](auto t) { return amount(t) == amount_; }
        );
        return found;
    }
};
}

#include <catch2/catch.hpp>

namespace finances { namespace {
class TransactionRecordTests {
    TransactionRecord record;
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, label, date};
    }

    std::vector<Transaction> onlyOne(
        int amount,
        std::string label,
        std::string date
    ) {
        return { transaction(amount, label, date) };
    }

    void add(int amount, std::string label, std::string date) {
        record.add(transaction(amount, label, date));
    }

    std::vector<Transaction> findByAmount(int amount) {
        return record.findByAmount(amount);
    }

    std::vector<Transaction> none() {
        return {};
    }
};

#define ASSERT_EQUAL(a, b) CHECK(a == b)
#define ASSERT_TRANSACTIONS_BY_AMOUNT(a, b) ASSERT_EQUAL(a, findByAmount(b))
#define ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(a, b, c, d)\
    ASSERT_TRANSACTIONS_BY_AMOUNT(onlyOne(a, b, c), d)
#define ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(a)\
    ASSERT_TRANSACTIONS_BY_AMOUNT(none(), a)

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountNone") {
    ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(0);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountNoneFound") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_NO_TRANSACTIONS_FOR_AMOUNT(0);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountOneFoundOnlyOne") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(-5000, "hyvee", "10/5/19", -5000);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountOneFound") {
    add(-5000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    ASSERT_ONLY_TRANSACTION_FOR_AMOUNT(-5000, "hyvee", "10/5/19", -5000);
}

TEST_CASE_METHOD(TransactionRecordTests, "findByAmountBothFound") {
    add(-1000, "hyvee", "10/5/19");
    add(-1000, "chipotle", "10/5/19");
    CHECK(
        std::vector<Transaction>{
            transaction(-1000, "hyvee", "10/5/19"),
            transaction(-1000, "chipotle", "10/5/19")
        } ==
        findByAmount(-1000)
    );
}
}}
