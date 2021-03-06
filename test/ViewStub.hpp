#ifndef TEST_VIEWSTUB_HPP_
#define TEST_VIEWSTUB_HPP_

#include <sbash64/finances/View.hpp>

namespace sbash64::finances {
class ViewStub : public View {
  public:
    auto shownTransactions() const { return shownTransactions_; }

    void show(const Transactions &t) override { shownTransactions_ = t; }

    void show(const NetIncome &x) override { shownNetIncome_ = x; }

    auto shownNetIncome() -> NetIncome { return shownNetIncome_; }

  private:
    Transactions shownTransactions_{};
    NetIncome shownNetIncome_{};
};
}

#endif
