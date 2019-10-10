#ifndef FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_
#define FINANCES_INCLUDE_FINANCES_FORMATTEDWRITER_HPP_

#include "Transaction.hpp"
#include "CommandInterpreter.hpp"
#include <string>

namespace finances {
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string formatTransactions(const Transactions &) = 0;
    virtual std::string formatNetIncome(int) = 0;
};

class Writer {
public:
    virtual ~Writer() = default;
    virtual void write(const std::string &) = 0;
};

class FormattedWriter : public Printer {
    Formatter &formatter;
    Writer &writer;
public:
    FormattedWriter(Formatter &, Writer &);
    void printTransactions(const Transactions &t) override;
    void printNetIncome(int x) override;
};
}

#endif
