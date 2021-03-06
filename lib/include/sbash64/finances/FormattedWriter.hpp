#ifndef FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_
#define FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_

#include "Transaction.hpp"
#include "CommandResponder.hpp"
#include <string>

namespace sbash64::finances {
class Formatter {
  public:
    virtual ~Formatter() = default;
    virtual auto format(const Transactions &) -> std::string = 0;
    virtual auto format(const NetIncome &) -> std::string = 0;
};

class Writer {
  public:
    virtual ~Writer() = default;
    virtual void write(const std::string &) = 0;
};

class FormattedWriter : public View {
  public:
    FormattedWriter(Formatter &, Writer &);
    void show(const Transactions &) override;
    void show(const NetIncome &) override;
    void show(const std::string &);

  private:
    Formatter &formatter;
    Writer &writer;
};
}

#endif
