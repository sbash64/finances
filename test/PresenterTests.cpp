#include "PresenterTests.hpp"
#include "ViewStub.hpp"
#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <sbash64/testcpplite/testcpplite.hpp>
#include <utility>
#include <functional>

namespace finances {
namespace {
void verified(Presenter &presenter, int a, std::string b, std::string c) {
    presenter.verified(transaction(a, std::move(b), std::move(c)));
}

void added(Presenter &presenter, int a, std::string b, std::string c) {
    presenter.added(transaction(a, std::move(b), std::move(c)));
}

void print(Presenter &presenter, const Transactions &t) { presenter.print(t); }

void assertTransactionsPrinted(
    sbash64::testcpplite::TestResult &result, ViewStub &view, const Transactions &t) {
    assertEqual(result, t, view.shownTransactions());
}

void assertTransactionPrinted(sbash64::testcpplite::TestResult &result, ViewStub &view,
    int amount, std::string label, std::string date) {
    assertTransactionsPrinted(result, view,
        oneTransaction(amount, std::move(label), std::move(date)));
}

void assertBothTransactionsPrinted(sbash64::testcpplite::TestResult &result,
    ViewStub &view, int amount1, std::string label1, std::string date1,
    int amount2, std::string label2, std::string date2) {
    assertTransactionsPrinted(result, view,
        twoTransactions(amount1, std::move(label1), std::move(date1), amount2,
            std::move(label2), std::move(date2)));
}

void assertNetIncomePrinted(
    sbash64::testcpplite::TestResult &result, ViewStub &view, int x) {
    assertEqual(result, x, view.shownNetIncome().cents);
}

void printNetIncome(Presenter &presenter, int x) {
    presenter.print(NetIncome{x});
}

void testPresenter(const std::function<void(Presenter &, ViewStub &)> &f) {
    ViewStub view;
    Presenter presenter{view};
    f(presenter, view);
}
}

void presenterPrintsTransactionVerified(sbash64::testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        verified(presenter, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void presenterPrintsTransactionAdded(sbash64::testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        added(presenter, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void presenterPrintsAllTransactions(sbash64::testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        print(presenter,
            twoTransactions(
                -1000, "chipotle", "10/6/19", -5000, "hyvee", "10/4/19"));
        assertBothTransactionsPrinted(result, view, -1000, "chipotle",
            "10/6/19", -5000, "hyvee", "10/4/19");
    });
}

void presenterPrintsNetIncome(sbash64::testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        printNetIncome(presenter, 5000);
        assertNetIncomePrinted(result, view, 5000);
    });
}
}
