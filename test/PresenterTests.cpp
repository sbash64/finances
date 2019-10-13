#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <catch2/catch.hpp>

namespace finances { namespace {
class ModelStub : public Model {
public:
    auto amountVerified() const {
        return amountVerified_;
    }

    auto transactionAdded() const {
        return transactionAdded_;
    }

    auto transactionRemoved() const {
        return transactionRemoved_;
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

    void setVerifiedTransactions(Transactions t) {
        verifiedTransactions_ = std::move(t);
    }

    void setUnverifiedTransactions(Transactions t) {
        unverifiedTransactions_ = std::move(t);
    }

    Transactions transactions() override {
        return transactions_;
    }

    int netIncome() override {
        return netIncome_;
    }

    void verify(int x) override {
        amountVerified_ = x;
    }

    void remove(const Transaction &t) override {
        transactionRemoved_ = t;
    }

    Transactions verifiedTransactions() override {
        return verifiedTransactions_;
    }

    Transactions unverifiedTransactions() override {
        return unverifiedTransactions_;
    }
private:
    Transactions transactions_;
    Transactions verifiedTransactions_;
    Transactions unverifiedTransactions_;
    Transaction transactionAdded_;
    Transaction transactionRemoved_;
    int netIncome_{};
    int amountVerified_{};
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

    Transaction transactionRemoved() {
        return model.transactionRemoved();
    }

    void setAllTransactions(Transactions t) {
        model.setTransactions(std::move(t));
    }

    void setVerifiedTransactions(Transactions t) {
        model.setVerifiedTransactions(std::move(t));
    }

    void setUnverifiedTransactions(Transactions t) {
        model.setUnverifiedTransactions(std::move(t));
    }

    Transactions printedTransactions() {
        return view.shownTransactions();
    }

    int printedNetIncome() {
        return view.shownNetIncome();
    }

    int amountVerified() {
        return model.amountVerified();
    }

    void executeCommand(Command c, const std::string &s = {}) {
        execute(name(c) + std::string(!s.empty(), ' ') + s);
    }

    void executeAdd(const std::string &s) {
        executeCommand(Command::add, s);
    }

    void executeRemove(const std::string &s) {
        executeCommand(Command::remove, s);
    }

    void executeVerify(const std::string &s) {
        executeCommand(Command::verify, s);
    }

    void executeNetIncome() {
        executeCommand(Command::netIncome);
    }

    void executePrint() {
        executeCommand(Command::print);
    }

    void executePrintVerified() {
        executeCommand(Command::printVerified);
    }

    void executePrintUnverified() {
        executeCommand(Command::printUnverified);
    }
private:
    ModelStub model;
    ViewStub view;
    Presenter presenter{model, view};
};

#define ASSERT_TRANSACTION_ADDED(a, b, c)\
    ASSERT_EQUAL(transaction(a, b, c), transactionAdded())

#define ASSERT_TRANSACTION_REMOVED(a, b, c)\
    ASSERT_EQUAL(transaction(a, b, c), transactionRemoved())

#define ASSERT_BOTH_TRANSACTIONS_PRINTED(a, b, c, d, e, f)\
    ASSERT_EQUAL(twoTransactions(a, b, c, d, e, f), printedTransactions())

#define ASSERT_NET_INCOME_PRINTED(a)\
    ASSERT_EQUAL(a, printedNetIncome())

#define ASSERT_AMOUNT_VERIFIED(a)\
    ASSERT_EQUAL(a, amountVerified())

#define PRESENTER_TEST(a)\
    TEST_CASE_METHOD(PresenterTests, a)

PRESENTER_TEST("addsTransaction") {
    executeAdd("-50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}

PRESENTER_TEST("addsAnotherTransaction") {
    executeAdd("-9.47 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-947, "chipotle", "10/6/19");
}

PRESENTER_TEST("oneDecimalDigit") {
    executeAdd("-9.4 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-940, "chipotle", "10/6/19");
}

PRESENTER_TEST("noDecimalDigits") {
    executeAdd("-9. chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-900, "chipotle", "10/6/19");
}

PRESENTER_TEST("removesTransaction") {
    executeRemove("-12.34 hyvee 10/5/19");
    ASSERT_TRANSACTION_REMOVED(-1234, "hyvee", "10/5/19");
}

PRESENTER_TEST("printPrintsAllTransactions") {
    setAllTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    ));
    executePrint();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    );
}

PRESENTER_TEST("printVerifiedPrintsVerifiedTransactions") {
    setVerifiedTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    ));
    executePrintVerified();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    );
}

PRESENTER_TEST("printUnverifiedTransactions") {
    setUnverifiedTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    ));
    executePrintUnverified();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19",
        -5000, "hyvee", "10/4/19"
    );
}

PRESENTER_TEST("netPrintsNetIncome") {
    setNetIncome(5000);
    executeNetIncome();
    ASSERT_NET_INCOME_PRINTED(5000);
}

PRESENTER_TEST("verifyVerifiesAmount") {
    executeVerify("-12.34");
    ASSERT_AMOUNT_VERIFIED(-1234);
}

PRESENTER_TEST("unrecognizedCommandDoesNotAbort") {
    execute("jellyfish");
}

PRESENTER_TEST("partiallyCorrectCommandDoesNotAbort") {
    executeAdd("oops");
}
}}
