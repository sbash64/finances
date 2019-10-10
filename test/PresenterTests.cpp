#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class TransactionRecordStub : public Model {
public:
    auto transactionAdded() const {
        return transactionAdded_;
    }

    void setNetIncome(int x) {
        netIncome_ = x;
    }

    void add(const Transaction &t) override {
        transactionAdded_ = t;
    }

    void setAll(Transactions t) {
        all_ = std::move(t);
    }

    Transactions transactions() override {
        return all_;
    }

    int netIncome() override {
        return netIncome_;
    }
private:
    Transactions all_;
    Transaction transactionAdded_;
    int netIncome_{};
};

class PrinterStub : public View {
public:
    auto printedTransactions() const {
        return printedTransactions_;
    }

    auto netIncome() const {
        return netIncome_;
    }

    void showTransactions(const Transactions &t) override {
        printedTransactions_ = t;
    }

    void showNetIncome(int x) override {
        netIncome_ = x;
    }
private:
    Transactions printedTransactions_;
    int netIncome_;
};

class PresenterTests {
    TransactionRecordStub record;
    PrinterStub printer;
    Presenter interpreter{record, printer};
protected:
    void execute(const std::string &s) {
        interpreter.execute(s);
    }

    void setNetIncome(int x) {
        record.setNetIncome(x);
    }

    Transaction transactionAdded() {
        return record.transactionAdded();
    }

    void setAllTransactions(Transactions t) {
        record.setAll(std::move(t));
    }

    Transactions printedTransactions() {
        return printer.printedTransactions();
    }

    int printedNetIncome() {
        return printer.netIncome();
    }
};

#define ASSERT_TRANSACTION_ADDED(a, b, c)\
    CHECK(transaction(a, b, c) == transactionAdded())
#define ASSERT_BOTH_TRANSACTIONS_PRINTED(a, b, c, d, e, f)\
    CHECK(\
        Transactions{\
            transaction(a, b, c), \
            transaction(d, e, f)\
        } == printedTransactions()\
    )
#define ASSERT_NET_INCOME_PRINTED(a) CHECK(a == printedNetIncome())

TEST_CASE_METHOD(PresenterTests, "addsTransaction") {
    execute("add -50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}

TEST_CASE_METHOD(PresenterTests, "addsAnotherTransaction") {
    execute("add -9.47 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-947, "chipotle", "10/6/19");
}

TEST_CASE_METHOD(PresenterTests, "printPrintsAllTransactions") {
    setAllTransactions({
        transaction(-1000, "chipotle", "10/6/19"),
        transaction(-5000, "hyvee", "10/4/19")
    });
    execute("print");
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    );
}

TEST_CASE_METHOD(PresenterTests, "netPrintsNetIncome") {
    setNetIncome(5000);
    execute("net");
    ASSERT_NET_INCOME_PRINTED(5000);
}
}}
