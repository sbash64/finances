#ifndef FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_
#define FINANCES_INCLUDE_FINANCES_PRESENTER_HPP_

#include "Transaction.hpp"
#include "Model.hpp"
#include "View.hpp"

namespace finances {
class Presenter : Model::EventListener {
  public:
    Presenter(Model &, View &);
    void verified(const Transaction &) override;
    void added(const Transaction &) override;

    enum class State { normal, amountEntered, labelEntered };

  private:
    View &view;
};
}

#endif
