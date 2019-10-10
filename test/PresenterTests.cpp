#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class ModelStub : public Model {
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

    void setTransactions(Transactions t) {
        transactions_ = std::move(t);
    }

    Transactions transactions() override {
        return transactions_;
    }

    int netIncome() override {
        return netIncome_;
    }
private:
    Transactions transactions_;
    Transaction transactionAdded_;
    int netIncome_{};
};

class ViewStub : public View {
public:
    auto shownTransactions() const {
        return shownTransactions_;
    }

    auto shownNetIncome() const {
        return shownNetIncome_;
    }

    void showTransactions(const Transactions &t) override {
        shownTransactions_ = t;
    }

    void showNetIncome(int x) override {
        shownNetIncome_ = x;
    }
private:
    Transactions shownTransactions_;
    int shownNetIncome_;
};

class PresenterTests {
    ModelStub model;
    ViewStub view;
    Presenter presenter{model, view};
protected:
    void execute(const std::string &s) {
        presenter.execute(s);
    }

    void setNetIncome(int x) {
        model.setNetIncome(x);
    }

    Transaction transactionAdded() {
        return model.transactionAdded();
    }

    void setAllTransactions(Transactions t) {
        model.setTransactions(std::move(t));
    }

    Transactions printedTransactions() {
        return view.shownTransactions();
    }

    int printedNetIncome() {
        return view.shownNetIncome();
    }
};

#define ASSERT_TRANSACTION_ADDED(a, b, c)\
    ASSERT_EQUAL(transaction(a, b, c), transactionAdded())
#define ASSERT_BOTH_TRANSACTIONS_PRINTED(a, b, c, d, e, f)\
    CHECK(\
        Transactions{\
            transaction(a, b, c), \
            transaction(d, e, f)\
        } == printedTransactions()\
    )
#define ASSERT_NET_INCOME_PRINTED(a) ASSERT_EQUAL(a, printedNetIncome())

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
