#include "CommandResponderTests.hpp"
#include "ViewStub.hpp"
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

    auto transactionWasAdded() const -> bool { return transactionWasAdded_; }

    auto transactionRemoved() const { return transactionRemoved_; }

    void setNetIncome(int x) { netIncome_.cents = x; }

    void add(const Transaction &t) override {
        transactionWasAdded_ = true;
        transactionAdded_ = t;
    }

    void setTransactions(Transactions t) { transactions_ = std::move(t); }

    void setVerifiedTransactions(Transactions t) {
        verifiedTransactions_ = std::move(t);
    }

    void setUnverifiedTransactions(Transactions t) {
        unverifiedTransactions_ = std::move(t);
    }

    auto transactions() -> Transactions override { return transactions_; }

    auto netIncome() -> NetIncome override { return netIncome_; }

    void verify(Amount x) override { amountVerified_ = x; }

    void remove(const Transaction &t) override { transactionRemoved_ = t; }

    auto verifiedTransactions() -> Transactions override {
        return verifiedTransactions_;
    }

    auto unverifiedTransactions() -> Transactions override {
        return unverifiedTransactions_;
    }

  private:
    Transactions transactions_;
    Transactions verifiedTransactions_;
    Transactions unverifiedTransactions_;
    Transaction transactionAdded_;
    Transaction transactionRemoved_;
    NetIncome netIncome_{};
    Amount amountVerified_{};
    bool transactionWasAdded_{};
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

void setNetIncome(ModelStub &model, int x) { model.setNetIncome(x); }

void execute(CommandResponder &commandResponder, const std::string &s) {
    commandResponder.enter(s);
}

void executeCommand(
    CommandResponder &commandResponder, Command c, const std::string &s = {}) {
    execute(
        commandResponder, name(c) + std::string(s.empty() ? 0 : 1, ' ') + s);
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
    assertEqual(result, x, view.shownNetIncome().cents);
}

void assertAmountVerified(
    testcpplite::TestResult &result, ModelStub &model, int x) {
    assertEqual(result, x, model.amountVerified().cents);
}

void testCommandResponder(
    const std::function<void(CommandResponder &, ModelStub &, ViewStub &)> &f) {
    ModelStub model;
    ViewStub view;
    CommandResponder commandResponder{model, view};
    f(commandResponder, model, view);
}
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

void commandResponderAddsTwoTransactionsInSteps(
    testcpplite::TestResult &result) {
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

void commandResponderDoesNotAddTransactionInSteps(
    testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            execute(commandResponder, "oops");
            execute(commandResponder, "hyvee");
            execute(commandResponder, "10/5/19");
            assertFalse(result, model.transactionWasAdded());
        });
}

void commandResponderAddsTransaction(testcpplite::TestResult &result) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &model, ViewStub &) {
            add(commandResponder, "-50 hyvee 10/5/19");
            assertTransactionAdded(result, model, -5000, "hyvee", "10/5/19");
        });
}

void commandResponderAddsTransactionWithDecimal(
    testcpplite::TestResult &result) {
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

void commandResponderPrintsAllTransactions(testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &commandResponder,
                             ModelStub &model, ViewStub &view) {
        setAllTransactions(model,
            twoTransactions(
                -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
        print(commandResponder);
        assertBothTransactionsPrinted(result, view, -1000, "chipotle",
            "10/6/19", -5000, "hyvee", "10/4/19");
    });
}

void commandResponderPrintsAllVerifiedTransaction(
    testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &commandResponder,
                             ModelStub &model, ViewStub &view) {
        setVerifiedTransactions(model,
            twoTransactions(
                -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
        printVerified(commandResponder);
        assertBothTransactionsPrinted(result, view, -1000, "chipotle",
            "10/6/19", -5000, "hyvee", "10/4/19");
    });
}

void commandResponderPrintsUnverifiedTransactions(
    testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &commandResponder,
                             ModelStub &model, ViewStub &view) {
        setUnverifiedTransactions(model,
            twoTransactions(
                -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
        printUnverified(commandResponder);
        assertBothTransactionsPrinted(result, view, -1000, "chipotle",
            "10/6/19", -5000, "hyvee", "10/4/19");
    });
}

void commandResponderPrintsNetIncome(testcpplite::TestResult &result) {
    testCommandResponder([&](CommandResponder &commandResponder,
                             ModelStub &model, ViewStub &view) {
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

void commandResponderDoesNotAbortOnUnrecognizedCommand(
    testcpplite::TestResult &) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &, ViewStub &) {
            execute(commandResponder, "jellyfish");
        });
}

void commandResponderDoesNotAbortOnInvalidNumber(testcpplite::TestResult &) {
    testCommandResponder(
        [&](CommandResponder &commandResponder, ModelStub &, ViewStub &) {
            execute(commandResponder, "1.2.3");
        });
}

void commandResponderDoesNotAbortOnPartiallyCorrectCommand(
    testcpplite::TestResult &) {
    testCommandResponder([&](CommandResponder &commandResponder, ModelStub &,
                             ViewStub &) { add(commandResponder, "oops"); });
}
}
