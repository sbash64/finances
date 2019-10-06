#ifndef FINANCES_FORMATTEDWRITER_HPP_
#define FINANCES_FORMATTEDWRITER_HPP_

#include "Transaction.hpp"
#include "CommandInterpreter.hpp"

namespace finances {
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(const Transactions &) = 0;
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
    FormattedWriter(Formatter &formatter, Writer &writer) :
        formatter{formatter},
        writer{writer} {}

    void print(const Transactions &t) override {
        writer.write('\n' + formatter.format(t) + "\n\n");
    }

    void printNetIncome(int x) override {
        formatter.formatNetIncome(x);
    }
};
}

#endif
