#include <string>
#include <vector>

namespace finances {
struct Transaction {
    int amount;
    std::string label;
    std::string date;
};

bool operator==(const Transaction &lhs, const Transaction &rhs) {
    return
        lhs.amount == rhs.amount &&
        lhs.label == rhs.label &&
        lhs.date == rhs.date;
}

class TransactionRecord {
    Transaction t;
public:
    void add(Transaction a) { t = a; }
    std::vector<Transaction> findByAmount(int) { return {t}; }
};
}

#include <catch2/catch.hpp>

#define ASSERT_EQUAL(a, b) CHECK(a == b)

namespace finances { namespace {
class TransactionRecordTests {
    TransactionRecord record;
protected:
    Transaction transaction(int amount, std::string label, std::string date) {
        return {amount, label, date};
    }

    std::vector<Transaction> oneTransaction(int amount, std::string label, std::string date) {
        return { transaction(amount, label, date) };
    }

    void add(int amount, std::string label, std::string date) {
        record.add(transaction(amount, label, date));
    }

    std::vector<Transaction> findByAmount(int amount) {
        return record.findByAmount(amount);
    }
};

TEST_CASE_METHOD(TransactionRecordTests, "tbd") {
    add(-5000, "hyvee", "10/5/19");
    ASSERT_EQUAL(oneTransaction(-5000, "hyvee", "10/5/19"), findByAmount(-50));
}
}}
