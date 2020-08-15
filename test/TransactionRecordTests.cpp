#include "testing-utility.hpp"
#include "TransactionRecordTests.hpp"
#include <sbash64/finances/TransactionRecord.hpp>
#include <sbash64/testcpplite/testcpplite.hpp>
#include <functional>

namespace finances {
namespace {
class ModelEventListenerStub : public TransactionRecord::EventListener {
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

void add(TransactionRecord &record, int amount, std::string label,
    std::string date) {
    record.add(transaction(amount, std::move(label), std::move(date)));
}

void verify(TransactionRecord &record, int amount) {
    record.verify(Amount{amount});
}

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

void assertTransactions(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, transactions(record));
}

void assertVerifiedTransactions(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, verifiedTransactions(record));
}

void assertUnverifiedTransactions(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, const Transactions &expected) {
    assertEqual(result, expected, record.unverifiedTransactions());
}

void assertNoTransactions(
    sbash64::testcpplite::TestResult &result, TransactionRecord &record) {
    assertTransactions(result, record, none());
}

void assertNoVerifiedTransactions(
    sbash64::testcpplite::TestResult &result, TransactionRecord &record) {
    assertVerifiedTransactions(result, record, none());
}

void assertOneTransaction(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertOneVerifiedTransaction(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertVerifiedTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertOneUnverifiedTransaction(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, int amount, std::string label,
    std::string date) {
    assertUnverifiedTransactions(result, record,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertTwoTransactions(sbash64::testcpplite::TestResult &result,
    TransactionRecord &record, int amount1, std::string label1,
    std::string date1, int amount2, std::string label2, std::string date2) {
    assertTransactions(result, record,
        twoTransactions(amount1, std::move(label1), std::move(date1), amount2,
            std::move(label2), std::move(date2)));
}

void testTransactionRecord(
    const std::function<void(TransactionRecord &, ModelEventListenerStub &)>
        &f) {
    ModelEventListenerStub listener;
    TransactionRecord record{listener};
    f(record, listener);
}

void assertNetIncome(
    sbash64::testcpplite::TestResult &result, TransactionRecord &record, int amount) {
    assertEqual(result, amount, record.netIncome().cents);
}
}

void transactionRecordHasNoneOnConstruction(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNoTransactions(result, record);
        });
}

void transactionRecordNotifiesListenerOnAdd(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -5000, "hyvee", "10/5/19");
            assertEqual(result, transaction(-5000, "hyvee", "10/5/19"),
                listener.addedTransaction());
        });
}

void transactionRecordHasOneAdded(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -5000, "hyvee", "10/5/19");
            assertOneTransaction(result, record, -5000, "hyvee", "10/5/19");
        });
}

void transactionRecordHasTwoAdded(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/5/19");
            assertTwoTransactions(result, record, -1000, "hyvee", "10/5/19",
                -1000, "chipotle", "10/5/19");
        });
}

void transactionRecordHasNoneAfterRemovingOne(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            remove(record, -1000, "hyvee", "10/5/19");
            assertNoTransactions(result, record);
        });
}

void transactionRecordHasThreeAdded(sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            remove(record, -2000, "hyvee", "10/5/19");
            assertNoTransactions(result, record);
        });
}

void transactionRecordHasOneAfterRemovingOne(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -5000, "hyvee", "10/5/19");
            add(record, -1000, "chipotle", "10/5/19");
            remove(record, -5000, "hyvee", "10/5/19");
            assertOneTransaction(result, record, -1000, "chipotle", "10/5/19");
        });
}

void transactionRecordHasTwoAfterRemovingOneNotFound(
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNetIncome(result, record, 0);
        });
}

void transactionRecordHasOneContributingNetIncome(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/5/19");
            assertNetIncome(result, record, -1000);
        });
}

void transactionRecordHasTwoContributingNetIncome(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -6132, "hyvee", "10/5/19");
            add(record, -1254, "chipotle", "10/5/19");
            assertNetIncome(result, record, -7386);
        });
}

void transactionRecordHasNoneVerifiedOnConstruction(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordHasNoneVerifiedAfterAdd(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordHasOneVerifiedAfterAdd(sbash64::testcpplite::TestResult &result) {
    testTransactionRecord([&](TransactionRecord &record,
                              ModelEventListenerStub &) {
        add(record, -2000, "hyvee", "10/5/19");
        verify(record, -2000);
        assertOneVerifiedTransaction(result, record, -2000, "hyvee", "10/5/19");
    });
}

void transactionRecordHasOneVerifiedAfterTwoAdded(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord([&](TransactionRecord &record,
                              ModelEventListenerStub &) {
        add(record, -2000, "hyvee", "10/5/19");
        add(record, -1000, "chipotle", "10/6/19");
        verify(record, -2000);
        assertOneVerifiedTransaction(result, record, -2000, "hyvee", "10/5/19");
    });
}

void transactionRecordHasTwoVerifiedAfterThreeAdded(
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            verify(record, -3000);
            assertNoVerifiedTransactions(result, record);
        });
}

void transactionRecordDoesNotNotifyAfterOneAddAndVerify(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -2000, "hyvee", "10/5/19");
            verify(record, -1000);
            sbash64::testcpplite::assertFalse(result, listener.verified());
        });
}

void transactionRecordNotiesAfterOneAddAndVerify(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &listener) {
            add(record, -2000, "hyvee", "10/5/19");
            verify(record, -2000);
            assertEqual(result, transaction(-2000, "hyvee", "10/5/19"),
                listener.verifiedTransaction());
        });
}

void transactionRecordHasNoneUnverifiedOnConstruction(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            assertUnverifiedTransactions(result, record, none());
        });
}

void transactionRecordHasOneUnverifiedAfterAdd(
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -1000, "hyvee", "10/1/19");
            assertOneUnverifiedTransaction(
                result, record, -1000, "hyvee", "10/1/19");
        });
}

void transactionRecordHasOneUnverifiedAfterTwoAdded(
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            verify(record, -2000);
            sbash64::testcpplite::assertEqual(result, Transactions::size_type{1},
                verifiedTransactions(record).size());
        });
}

void transactionRecordVerifiesMatchingAmountWhenRemovingFirst(
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
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
    sbash64::testcpplite::TestResult &result) {
    testTransactionRecord(
        [&](TransactionRecord &record, ModelEventListenerStub &) {
            add(record, -2000, "hyvee", "10/5/19");
            add(record, -2000, "chipotle", "10/6/19");
            remove(record, -2000, "chipotle", "10/6/19");
            assertNoVerifiedTransactions(result, record);
        });
}
}
