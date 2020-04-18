#include "PresenterTests.hpp"
#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <testcpplite/testcpplite.hpp>
#include <catch2/catch.hpp>
#include <utility>
#include <functional>

namespace finances {
namespace {
class ModelStub : public Model {
  public:
    auto amountVerified() const { return amountVerified_; }

    auto transactionAdded() const { return transactionAdded_; }

    auto transactionRemoved() const { return transactionRemoved_; }

    void setNetIncome(int x) { netIncome_ = x; }

    void add(const Transaction &t) override { transactionAdded_ = t; }

    void setTransactions(Transactions t) { transactions_ = std::move(t); }

    void setVerifiedTransactions(Transactions t) {
        verifiedTransactions_ = std::move(t);
    }

    void setUnverifiedTransactions(Transactions t) {
        unverifiedTransactions_ = std::move(t);
    }

    auto transactions() -> Transactions override { return transactions_; }

    auto netIncome() -> int override { return netIncome_; }

    void verify(int x) override { amountVerified_ = x; }

    void remove(const Transaction &t) override { transactionRemoved_ = t; }

    auto verifiedTransactions() -> Transactions override {
        return verifiedTransactions_;
    }

    auto unverifiedTransactions() -> Transactions override {
        return unverifiedTransactions_;
    }

    void subscribe(EventListener *e) override {
        listener = e;
        subscribed_ = true;
    }

    auto subscribed() const -> bool { return subscribed_; }

    auto verified(const Transaction &t) { listener->verified(t); }

    auto added(const Transaction &t) { listener->added(t); }

  private:
    Transactions transactions_;
    Transactions verifiedTransactions_;
    Transactions unverifiedTransactions_;
    Transaction transactionAdded_;
    Transaction transactionRemoved_;
    EventListener *listener{};
    int netIncome_{};
    int amountVerified_{};
    bool subscribed_{};
};

class ViewStub : public View {
  public:
    auto shownTransactions() const { return shownTransactions_; }

    auto shownNetIncome() const { return shownNetIncome_; }

    void show(const Transactions &t) override { shownTransactions_ = t; }

    void showNetIncome(int x) override { shownNetIncome_ = x; }

  private:
    Transactions shownTransactions_;
    int shownNetIncome_;
};

class PresenterTests {
  protected:
    void execute(const std::string &s) { presenter.execute(s); }

    void setNetIncome(int x) { model.setNetIncome(x); }

    auto transactionAdded() -> Transaction { return model.transactionAdded(); }

    auto transactionRemoved() -> Transaction {
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

    auto printedTransactions() -> Transactions {
        return view.shownTransactions();
    }

    auto printedNetIncome() -> int { return view.shownNetIncome(); }

    auto amountVerified() -> int { return model.amountVerified(); }

    void executeCommand(Command c, const std::string &s = {}) {
        execute(name(c) + std::string(s.empty() ? 0 : 1, ' ') + s);
    }

    void executeAdd(const std::string &s) { executeCommand(Command::add, s); }

    void executeRemove(const std::string &s) {
        executeCommand(Command::remove, s);
    }

    void executeVerify(const std::string &s) {
        executeCommand(Command::verify, s);
    }

    void executeNetIncome() { executeCommand(Command::netIncome); }

    void executePrint() { executeCommand(Command::print); }

    void executePrintVerified() { executeCommand(Command::printVerified); }

    void executePrintUnverified() { executeCommand(Command::printUnverified); }

    void verified(int a, std::string b, std::string c) {
        model.verified(transaction(a, std::move(b), std::move(c)));
    }

    void added(int a, std::string b, std::string c) {
        model.added(transaction(a, std::move(b), std::move(c)));
    }

    auto subscribedToModelEvents() -> bool { return model.subscribed(); }

  private:
    ModelStub model;
    ViewStub view;
    Presenter presenter{model, view};
};

void setAllTransactions(ModelStub &model, Transactions t) {
    model.setTransactions(std::move(t));
}

void verified(ModelStub &model, int a, std::string b, std::string c) {
    model.verified(transaction(a, std::move(b), std::move(c)));
}

void added(ModelStub &model, int a, std::string b, std::string c) {
    model.added(transaction(a, std::move(b), std::move(c)));
}

void execute(Presenter &presenter, const std::string &s) {
    presenter.execute(s);
}

void executeCommand(
    Presenter &presenter, Command c, const std::string &s = {}) {
    execute(presenter, name(c) + std::string(s.empty() ? 0 : 1, ' ') + s);
}

void executeAdd(Presenter &presenter, const std::string &s) {
    executeCommand(presenter, Command::add, s);
}

void executeRemove(Presenter &presenter, const std::string &s) {
    executeCommand(presenter, Command::remove, s);
}

void executePrint(Presenter &presenter) {
    executeCommand(presenter, Command::print);
}

void assertTransactionAdded(testcpplite::TestResult &result, ModelStub &model,
    int amount, std::string label, std::string date) {
    assertEqual(result, transaction(amount, std::move(label), std::move(date)),
        model.transactionAdded());
}

void assertTransactionRemoved(testcpplite::TestResult &result, ModelStub &model,
    int amount, std::string label, std::string date) {
    assertEqual(result, transaction(amount, std::move(label), std::move(date)),
        model.transactionRemoved());
}

void assertTransactionPrinted(testcpplite::TestResult &result, ViewStub &view,
    int amount, std::string label, std::string date) {
    assertEqual(result,
        oneTransaction(amount, std::move(label), std::move(date)),
        view.shownTransactions());
}

void assertBothTransactionsPrinted(testcpplite::TestResult &result,
    ViewStub &view, int amount1, std::string label1, std::string date1,
    int amount2, std::string label2, std::string date2) {
    assertEqual(result,
        twoTransactions(amount1, std::move(label1), std::move(date1), amount2,
            std::move(label2), std::move(date2)),
        view.shownTransactions());
}

void testPresenter(
    const std::function<void(Presenter &, ModelStub &, ViewStub &)> &f) {
    ModelStub model;
    ViewStub view;
    Presenter presenter{model, view};
    f(presenter, model, view);
}

#define ASSERT_TRANSACTION_ADDED(a, b, c)                                      \
    ASSERT_EQUAL(transaction(a, b, c), transactionAdded())

#define ASSERT_TRANSACTION_REMOVED(a, b, c)                                    \
    ASSERT_EQUAL(transaction(a, b, c), transactionRemoved())

#define ASSERT_PRINTED_TRANSACTIONS(a) ASSERT_EQUAL(a, printedTransactions())

#define ASSERT_BOTH_TRANSACTIONS_PRINTED(a, b, c, d, e, f)                     \
    ASSERT_PRINTED_TRANSACTIONS(twoTransactions(a, b, c, d, e, f))

#define ASSERT_TRANSACTION_PRINTED(a, b, c)                                    \
    ASSERT_PRINTED_TRANSACTIONS(oneTransaction(a, b, c))

#define ASSERT_NET_INCOME_PRINTED(a) ASSERT_EQUAL(a, printedNetIncome())

#define ASSERT_AMOUNT_VERIFIED(a) ASSERT_EQUAL(a, amountVerified())

#define ASSERT_SUBSCRIBED_TO_MODEL_EVENTS()                                    \
    ASSERT_TRUE(subscribedToModelEvents())

#define PRESENTER_TEST(a) TEST_CASE_METHOD(PresenterTests, a)

PRESENTER_TEST("subscribesToModelEvents") {
    ASSERT_SUBSCRIBED_TO_MODEL_EVENTS();
}
}

void presenterSubscribesToModelEvents(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &) {
        assertTrue(result, model.subscribed());
    });
}

namespace {
PRESENTER_TEST("addTransactionParsesInput") {
    executeAdd("-50 hyvee 10/5/19");
    ASSERT_TRANSACTION_ADDED(-5000, "hyvee", "10/5/19");
}
}

void presenterAddsTransaction(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &) {
        executeAdd(presenter, "-50 hyvee 10/5/19");
        assertTransactionAdded(result, model, -5000, "hyvee", "10/5/19");
    });
}

namespace {

PRESENTER_TEST("addTransactionParsesDecimal") {
    executeAdd("-9.47 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-947, "chipotle", "10/6/19");
}
}

void presenterAddsTransactionWithDecimal(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &) {
        executeAdd(presenter, "-9.47 chipotle 10/6/19");
        assertTransactionAdded(result, model, -947, "chipotle", "10/6/19");
    });
}

namespace {

PRESENTER_TEST("addTransactionParsesOneDecimalDigit") {
    executeAdd("-9.4 chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-940, "chipotle", "10/6/19");
}
}

void presenterAddsTransactionWithOneDecimalDigit(
    testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &) {
        executeAdd(presenter, "-9.4 chipotle 10/6/19");
        assertTransactionAdded(result, model, -940, "chipotle", "10/6/19");
    });
}

namespace {

PRESENTER_TEST("addTransactionParsesNoDecimalDigits") {
    executeAdd("-9. chipotle 10/6/19");
    ASSERT_TRANSACTION_ADDED(-900, "chipotle", "10/6/19");
}
}

void presenterAddsTransactionWithNoDecimalDigits(
    testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &) {
        executeAdd(presenter, "-9. chipotle 10/6/19");
        assertTransactionAdded(result, model, -900, "chipotle", "10/6/19");
    });
}

namespace {

PRESENTER_TEST("removeTransactionParsesInput") {
    executeRemove("-12.34 hyvee 10/5/19");
    ASSERT_TRANSACTION_REMOVED(-1234, "hyvee", "10/5/19");
}
}

void presenterRemovesTransaction(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &) {
        executeRemove(presenter, "-12.34 hyvee 10/5/19");
        assertTransactionRemoved(result, model, -1234, "hyvee", "10/5/19");
    });
}

namespace {

PRESENTER_TEST("verifiedEventPrintsTransaction") {
    verified(-1000, "chipotle", "10/6/19");
    ASSERT_TRANSACTION_PRINTED(-1000, "chipotle", "10/6/19");
}
}

void presenterPrintsTransactionVerified(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &view) {
        verified(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

namespace {

PRESENTER_TEST("addedEventPrintsTransaction") {
    added(-1000, "chipotle", "10/6/19");
    ASSERT_TRANSACTION_PRINTED(-1000, "chipotle", "10/6/19");
}
}

void presenterPrintsTransactionAdded(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &view) {
        added(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

namespace {

PRESENTER_TEST("printPrintsAllTransactions") {
    setAllTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
    executePrint();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19");
}
}

void presenterPrintsAllTransaction(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ModelStub &model, ViewStub &view) {
        setAllTransactions(model,
            twoTransactions(
                -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
        executePrint(presenter);
        assertBothTransactionsPrinted(result, view, -1000, "chipotle",
            "10/6/19", -5000, "hyvee", "10/4/19");
    });
}

namespace {

PRESENTER_TEST("printVerifiedPrintsVerifiedTransactions") {
    setVerifiedTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
    executePrintVerified();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19");
}

PRESENTER_TEST("printUnverifiedPrintsUnverifiedTransactions") {
    setUnverifiedTransactions(twoTransactions(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
    executePrintUnverified();
    ASSERT_BOTH_TRANSACTIONS_PRINTED(
        -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19");
}

PRESENTER_TEST("netIncomePrintsNetIncome") {
    setNetIncome(5000);
    executeNetIncome();
    ASSERT_NET_INCOME_PRINTED(5000);
}

PRESENTER_TEST("verifyParsesInput") {
    executeVerify("-12.34");
    ASSERT_AMOUNT_VERIFIED(-1234);
}

PRESENTER_TEST("unrecognizedCommandDoesNotAbort") { execute("jellyfish"); }

PRESENTER_TEST("partiallyCorrectCommandDoesNotAbort") { executeAdd("oops"); }

// clang-format on

}
}
