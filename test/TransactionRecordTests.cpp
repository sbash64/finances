#include "testing-utility.hpp"
#include "TransactionRecordTests.hpp"
#include <finances/TransactionRecord.hpp>
#include <testcpplite/testcpplite.hpp>
#include <functional>

namespace finances {
namespace {
class ModelEventListenerStub : public Model::EventListener {
  public:
    auto verified() const -> bool { return verified_; }

    auto verifiedTransaction() const -> Transaction {
        return verifiedTransaction_;
    }

    auto addedTransaction() const -> Transaction { return addedTransaction_; }

    void verified(const Transaction &t) override {
        verifiedTransaction_ = t;
        verified_ = true;
    }

    void added(const Transaction &t) override { addedTransaction_ = t; }

  private:
    Transaction verifiedTransaction_{};
    Transaction addedTransaction_{};
    bool verified_{};
};

auto none() -> Transactions { return {}; }

void assertEqual(testcpplite::TestResult &result, const Transaction &expected,
    const Transaction &actual) {
    assertEqual(result, expected.amount, actual.amount);
    assertEqual(result, expected.date, actual.date);
    assertEqual(result, expected.label, actual.label);
}

void assertEqual(testcpplite::TestResult &result, const Transactions &expected,
    const Transactions &actual) {
    assertEqual(result, expected.size(), actual.size());
    for (size_t i{0}; i < expected.size(); ++i)
        assertEqual(result, expected.at(i), actual.at(i));
}

void add(TransactionRecord &record, int amount, std::string label,
    std::string date) {
    record.add(transaction(amount, std::move(label), std::move(date)));
}

void verify(TransactionRecord &record, int amount) { record.verify(amount); }

void remove(TransactionRecord &record, int amount, std::string label,
    std::string date) {
    record.remove(transaction(amount, std::move(label), std::move(date)));
}

auto transactions(TransactionRecord &record) -> Transactions {
    return record.transactions();
}

auto verifiedTransactions(TransactionRecord &record) -> Transactions {
    return record.verifiedTransactions();
}

void assertTransactions(testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, transactions(record));
}

void assertVerifiedTransactions(testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, verifiedTransactions(record));
}

void assertUnverifiedTransactions(testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, record.unverifiedTransactions());
}

void assertNoTransactions(
    testcpplite::TestResult &result, TransactionRecord &record) {
    assertTransactions(result, record, none());
}

void assertNoVerifiedTransactions(
    testcpplite::TestResult &result, TransactionRecord &record) {
    assertVerifiedTransactions(result, record, none());
}

void assertOneTransaction(testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertOneVerifiedTransaction(testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertVerifiedTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertOneUnverifiedTransaction(testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertUnverifiedTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertTwoTransactions(testcpplite::TestResult &result,
    TransactionRecord &record, int amount1, std::string label1,
    std::string date1, int amount2, std::string label2, std::string date2) {
    assertTransactions(result, record,
        twoTransactions(amount1, std::move(label1), std::move(date1), amount2,
            std::move(label2), std::move(date2)));
}

void testTransactionRecord(
    const std::function<void(TransactionRecord &, ModelEventListenerStub &)>
        &f) {
    TransactionRecord record;
    ModelEventListenerStub listener;
    record.subscribe(&listener);
    f(record, listener);
}

void assertNetIncome(
    testcpplite::TestResult &result, TransactionRecord &record, int amount) {
    assertEqual(result, amount, record.netIncome());
}
}

void transactionRecordHasNoneOnConstruction(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNoTransactions(result, record);
        });
}

void transactionRecordNotifiesListenerOnAdd(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -5000, "hyvee", "10/5/19");
            assertEqual(result, transaction(-5000, "hyvee", "10/5/19"),
                listener.addedTransaction());
        });
}

void transactionRecordHasOneAdded(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -5000, "hyvee", "10/5/19");
            assertOneTransaction(result, record, -5000, "hyvee", "10/5/19");
        });
}

void transactionRecordHasTwoAdded(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/5/19");
            assertTwoTransactions(result, record, -1000, "hyvee", "10/5/19",
                -1000, "chipotle", "10/5/19");
        });
}

void transactionRecordHasNoneAfterRemovingOne(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            remove(record, -1000, "hyvee", "10/5/19");
            assertNoTransactions(result, record);
        });
}

void transactionRecordHasThreeAdded(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -3000, "walmart", "10/4/19");
            add(record, -1000, "chipotle", "10/6/19");
            assertTransactions(result, record,
                threeTransactions(-2000, "hyvee", "10/5/19", -3000, "walmart",
                    "10/4/19", -1000, "chipotle", "10/6/19"));
        });
}

void transactionRecordHasNoneAfterRemovingNone(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            remove(record, -2000, "hyvee", "10/5/19");
            assertNoTransactions(result, record);
        });
}

void transactionRecordHasOneAfterRemovingOne(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -5000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/5/19");
            remove(record, -5000, "hyvee", "10/5/19");
            assertOneTransaction(result, record, -1000, "chipotle", "10/5/19");
        });
}

void transactionRecordHasTwoAfterRemovingOneNotFound(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -5000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/5/19");
            remove(record, -4999, "hyvee", "10/5/19");
            assertTwoTransactions(result, record, -5000, "hyvee", "10/5/19",
                -1000, "chipotle", "10/5/19");
        });
}

void transactionRecordHasZeroNetIncomeOnConstruction(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNetIncome(result, record, 0);
        });
}

void transactionRecordHasOneContributingNetIncome(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            assertNetIncome(result, record, -1000);
        });
}

void transactionRecordHasTwoContributingNetIncome(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -6132, "hyvee", "10/5/19");
            add(record, -1254, "chipotle", "10/5/19");
            assertNetIncome(result, record, -7386);
        });
}

void transactionRecordHasNoneVerifiedOnConstruction(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordHasNoneVerifiedAfterAdd(testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordHasOneVerifiedAfterAdd(testcpplite::TestResult &result) {
    testTransactionRecord([&](TransactionRecord &record,
                              ModelEventListenerStub &) {
        add(record, -2000, "hyvee", "10/5/19");
        verify(record, -2000);
        assertOneVerifiedTransaction(result, record, -2000, "hyvee", "10/5/19");
    });
}

void transactionRecordHasOneVerifiedAfterTwoAdded(
    testcpplite::TestResult &result) {
    testTransactionRecord([&](TransactionRecord &record,
                              ModelEventListenerStub &) {
        add(record, -2000, "hyvee", "10/5/19");
        add(record, -1000, "chipotle", "10/6/19");
        verify(record, -2000);
        assertOneVerifiedTransaction(result, record, -2000, "hyvee", "10/5/19");
    });
}

void transactionRecordHasTwoVerifiedAfterThreeAdded(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/6/19");
            add(record, -3000, "barnes noble", "10/4/19");
            verify(record, -2000);
            verify(record, -3000);
            assertVerifiedTransactions(result, record,
                twoTransactions(-2000, "hyvee", "10/5/19", -3000,
                    "barnes noble", "10/4/19"));
        });
}

void transactionRecordHasNoneVerifiedAfterVerify(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            verify(record, -3000);
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordDoesNotNotifyAfterOneAddAndVerify(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -2000, "hyvee", "10/5/19");
            verify(record, -1000);
            testcpplite::assertFalse(result, listener.verified());
        });
}

void transactionRecordNotiesAfterOneAddAndVerify(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -2000, "hyvee", "10/5/19");
            verify(record, -2000);
            assertEqual(result, transaction(-2000, "hyvee", "10/5/19"),
                listener.verifiedTransaction());
        });
}

void transactionRecordHasNoneUnverifiedOnConstruction(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertUnverifiedTransactions(result, record, none());
        });
}

void transactionRecordHasOneUnverifiedAfterAdd(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/1/19");
            assertOneUnverifiedTransaction(
                result, record, -1000, "hyvee", "10/1/19");
        });
}

void transactionRecordHasOneUnverifiedAfterTwoAdded(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/6/19");
            verify(record, -2000);
            assertOneUnverifiedTransaction(
                result, record, -1000, "chipotle", "10/6/19");
        });
}

void transactionRecordHasTwoVerifiedOfSameAmount(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            verify(record, -2000);
            verify(record, -2000);
            assertVerifiedTransactions(result, record,
                twoTransactions(
                    -2000, "hyvee", "10/5/19", -2000, "chipotle", "10/6/19"));
        });
}

void transactionRecordHasOneVerifiedAfterAddingTwoOfSameAmount(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            verify(record, -2000);
            testcpplite::assertEqual(result, Transactions::size_type{1},
                verifiedTransactions(record).size());
        });
}

void transactionRecordVerifiesMatchingAmountWhenRemovingFirst(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            verify(record, -2000);
            remove(record, -2000, "hyvee", "10/5/19");
            assertOneVerifiedTransaction(
                result, record, -2000, "chipotle", "10/6/19");
        });
}

void transactionRecordVerifiesMatchingAmountWhenRemovingSecond(
    testcpplite::TestResult &result) {
    testTransactionRecord([&](TransactionRecord &record,
                              ModelEventListenerStub &) {
        add(record, -2000, "hyvee", "10/5/19");
        add(record, -2000, "chipotle", "10/6/19");
        verify(record, -2000);
        remove(record, -2000, "chipotle", "10/6/19");
        assertOneVerifiedTransaction(result, record, -2000, "hyvee", "10/5/19");
    });
}

void transactionRecordDoesNotVerifyMatchingAmountWhenRemovingOne(
    testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            remove(record, -2000, "chipotle", "10/6/19");
            assertNoVerifiedTransactions(result, record);
        });
}
}
