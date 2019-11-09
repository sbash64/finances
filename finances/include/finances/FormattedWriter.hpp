#ifndef FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_
#define FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_

#include "Transaction.hpp"
#include "Presenter.hpp"
#include <string>

namespace finances {
class Formatter {
  public:
    virtual ~Formatter() = default;
    virtual auto formatTransactions(const Transactions &) -> std::string = 0;
    virtual auto formatNetIncome(int) -> std::string = 0;
};

class Writer {
  public:
    virtual ~Writer() = default;
    virtual void write(const std::string &) = 0;
};

class FormattedWriter : public View {
  public:
    FormattedWriter(Formatter &, Writer &);
    void showTransactions(const Transactions &t) override;
    void showNetIncome(int x) override;

  private:
    Formatter &formatter;
    Writer &writer;
};
}

#endif
