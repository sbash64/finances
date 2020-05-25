#include "PresenterTests.hpp"
#include "testing-utility.hpp"
#include <finances/Presenter.hpp>
#include <testcpplite/testcpplite.hpp>
#include <utility>
#include <functional>

namespace finances {
namespace {
class ModelStub : public Model {
  public:
    void add(const Transaction &t) override { transactionAdded_ = t; }

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

    void show(const Transactions &t) override { shownTransactions_ = t; }

    void showNetIncome(int x) override { shownNetIncome_ = x; }

  private:
    Transactions shownTransactions_;
    int shownNetIncome_;
};

void verified(ModelStub &model, int a, std::string b, std::string c) {
    model.verified(transaction(a, std::move(b), std::move(c)));
}

void added(ModelStub &model, int a, std::string b, std::string c) {
    model.added(transaction(a, std::move(b), std::move(c)));
}

void assertTransactionPrinted(testcpplite::TestResult &result, ViewStub &view,
    int amount, std::string label, std::string date) {
    assertEqual(result,
        oneTransaction(amount, std::move(label), std::move(date)),
        view.shownTransactions());
}

void testPresenter(
    const std::function<void(Presenter &, ModelStub &, ViewStub &)> &f) {
    ModelStub model;
    ViewStub view;
    Presenter presenter{model, view};
    f(presenter, model, view);
}
}

void presenterSubscribesToModelEvents(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &) {
        assertTrue(result, model.subscribed());
    });
}

void presenterPrintsTransactionVerified(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &view) {
        verified(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}

void presenterPrintsTransactionAdded(testcpplite::TestResult &result) {
    testPresenter([&](Presenter &, ModelStub &model, ViewStub &view) {
        added(model, -1000, "chipotle", "10/6/19");
        assertTransactionPrinted(result, view, -1000, "chipotle", "10/6/19");
    });
}
}
