#include "CommandResponderTests.hpp"
#include "testing-utility.hpp"
#include <finances/CommandResponder.hpp>
#include <testcpplite/testcpplite.hpp>
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

void setAllTransactions(ModelStub &model, Transactions t) {
    model.setTransactions(std::move(t));
}

void setVerifiedTransactions(ModelStub &model, Transactions t) {
    model.setVerifiedTransactions(std::move(t));
}

void setUnverifiedTransactions(ModelStub &model, Transactions t) {
    model.setUnverifiedTransactions(std::move(t));
}

void verified(ModelStub &model, int a, std::string b, std::string c) {
    model.verified(transaction(a, std::move(b), std::move(c)));
}

void added(ModelStub &model, int a, std::string b, std::string c) {
    model.added(transaction(a, std::move(b), std::move(c)));
}

void setNetIncome(ModelStub &model, int x) { model.setNetIncome(x); }

void execute(CommandResponder &commandResponder, const std::string &s) {
    commandResponder.execute(s);
}

void executeCommand(
    CommandResponder &commandResponder, Command c, const std::string &s = {}) {
    execute(commandResponder, name(c) + std::string(s.empty() ? 0 : 1, ' ') + s);
}

void add(CommandResponder &commandResponder, const std::string &s) {
    executeCommand(commandResponder, Command::add, s);
}

void remove(CommandResponder &commandResponder, const std::string &s) {
    executeCommand(commandResponder, Command::remove, s);
}

void print(CommandResponder &commandResponder) {
    executeCommand(commandResponder, Command::print);
}

void printVerified(CommandResponder &commandResponder) {
    executeCommand(commandResponder, Command::printVerified);
}

void printUnverified(CommandResponder &commandResponder) {
    executeCommand(commandResponder, Command::printUnverified);
}

void netIncome(CommandResponder &commandResponder) {
    executeCommand(commandResponder, Command::netIncome);
}

void verify(CommandResponder &commandResponder, const std::string &s) {
    executeCommand(commandResponder, Command::verify, s);
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

void assertNetIncomePrinted(
    testcpplite::TestResult &result, ViewStub &view, int x) {
    assertEqual(result, x, view.shownNetIncome());
}

void assertAmountVerified(
    testcpplite::TestResult &result, ModelStub &model, int x) {
    assertEqual(result, x, model.amountVerified());
}

void testCommandResponder(
    const std::function<void(CommandResponder &, ModelStub &, ViewStub &)> &f) {
    ModelStub model;
    ViewStub view;
    CommandResponder commandResponder{model, view};
    f(commandResponder, model, view);
}
}

void commandResponderSubscribesToModelEvents(testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &, ModelStub &model, ViewStub &) {
        assertTrue(result, model.subscribed());
    });
}

void commandResponderAddsTransactionInSteps(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            execute(commandResponder, "-50");
            execute(commandResponder, "hyvee");
            execute(commandResponder, "10/5/19");
            assertTransactionAdded(result, model, -5000, "hyvee", "10/5/19");
        });
}

void commandResponderAddsTwoTransactionsInSteps(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            execute(commandResponder, "-50");
            execute(commandResponder, "hyvee");
            execute(commandResponder, "10/5/19");
            execute(commandResponder, "-9.47");
            execute(commandResponder, "chipotle");
            execute(commandResponder, "10/6/19");
            assertTransactionAdded(result, model, -947, "chipotle", "10/6/19");
        });
}

void commandResponderAddsTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            add(commandResponder, "-50 hyvee 10/5/19");
            assertTransactionAdded(result, model, -5000, "hyvee", "10/5/19");
        });
}

void commandResponderAddsTransactionWithDecimal(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            add(commandResponder, "-9.47 chipotle 10/6/19");
            assertTransactionAdded(result, model, -947, "chipotle", "10/6/19");
        });
}

void commandResponderAddsTransactionWithOneDecimalDigit(
    testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            add(commandResponder, "-9.4 chipotle 10/6/19");
            assertTransactionAdded(result, model, -940, "chipotle", "10/6/19");
        });
}

void commandResponderAddsTransactionWithNoDecimalDigits(
    testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            add(commandResponder, "-9. chipotle 10/6/19");
            assertTransactionAdded(result, model, -900, "chipotle", "10/6/19");
        });
}

void commandResponderRemovesTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            remove(commandResponder, "-12.34 hyvee 10/5/19");
            assertTransactionRemoved(result, model, -1234, "hyvee", "10/5/19");
        });
}

void commandResponderPrintsTransactionVerified(testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &, ModelStub &model, ViewStub &view) {
        verified(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void commandResponderPrintsTransactionAdded(testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &, ModelStub &model, ViewStub &view) {
        added(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void commandResponderPrintsAllTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &view) {
            setAllTransactions(model,
                twoTransactions(
                    -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
            print(commandResponder);
            assertBothTransactionsPrinted(result, view, -1000, "chipotle",
                "10/6/19", -5000, "hyvee", "10/4/19");
        });
}

void commandResponderPrintsAllVerifiedTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &view) {
            setVerifiedTransactions(model,
                twoTransactions(
                    -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
            printVerified(commandResponder);
            assertBothTransactionsPrinted(result, view, -1000, "chipotle",
                "10/6/19", -5000, "hyvee", "10/4/19");
        });
}

void commandResponderPrintsUnverifiedTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &view) {
            setUnverifiedTransactions(model,
                twoTransactions(
                    -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
            printUnverified(commandResponder);
            assertBothTransactionsPrinted(result, view, -1000, "chipotle",
                "10/6/19", -5000, "hyvee", "10/4/19");
        });
}

void commandResponderPrintsNetIncome(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &view) {
            setNetIncome(model, 5000);
            netIncome(commandResponder);
            assertNetIncomePrinted(result, view, 5000);
        });
}

void commandResponderVerifiesAmount(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            verify(commandResponder, "-12.34");
            assertAmountVerified(result, model, -1234);
        });
}

void commandResponderDoesNotAbortOnUnrecognizedCommand(testcpplite::TestResult &) {
    testCommandResponder([&](CommandResponder &commandResponder, ModelStub &, ViewStub &) {
        execute(commandResponder, "jellyfish");
    });
}

void commandResponderDoesNotAbortOnPartiallyCorrectCommand(testcpplite::TestResult &) {
    testCommandResponder([&](CommandResponder &commandResponder, ModelStub &, ViewStub &) {
        add(commandResponder, "oops");
    });
}
}
