#include "PresenterTests.hpp"
#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <testcpplite/testcpplite.hpp>
#include <utility>
#include <functional>

namespace finances {
namespace {
class ViewStub : public View {
  public:
    auto shownTransactions() const { return shownTransactions_; }

    void show(const Transactions &t) override { shownTransactions_ = t; }

    void show(const NetIncome &x) override { shownNetIncome_ = x; }

  private:
    Transactions shownTransactions_{};
    NetIncome shownNetIncome_{};
};

void verified(Presenter &presenter, int a, std::string b, std::string c) {
    presenter.verified(transaction(a, std::move(b), std::move(c)));
}

void added(Presenter &presenter, int a, std::string b, std::string c) {
    presenter.added(transaction(a, std::move(b), std::move(c)));
}

void assertTransactionPrinted(testcpplite::TestResult &result, ViewStub &view,
    int amount, std::string label, std::string date) {
    assertEqual(result,
        oneTransaction(amount, std::move(label), std::move(date)),
        view.shownTransactions());
}

void testPresenter(const std::function<void(Presenter &, ViewStub &)> &f) {
    ViewStub view;
    Presenter presenter{view};
    f(presenter, view);
}
}

void presenterPrintsTransactionVerified(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        verified(presenter, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void presenterPrintsTransactionAdded(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &presenter, ViewStub &view) {
        added(presenter, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}
}
