#ifndef FINANCES_FORMATTEDWRITER_HPP_
#define FINANCES_FORMATTEDWRITER_HPP_

#include <finances/Transaction.hpp>

namespace finances {
class Formatter {
public:
    virtual ~Formatter() = default;
    virtual std::string format(const Transactions &) = 0;
};

class Writer {
public:
    virtual ~Writer() = default;
    virtual void write(const std::string &) = 0;
};

class FormattedWriter {
    Formatter &formatter;
    Writer &writer;
public:
    FormattedWriter(Formatter &formatter, Writer &writer) :
        formatter{formatter},
        writer{writer} {}

    void print(const Transactions &t) {
        writer.write(formatter.format(t));
    }
};
}

#endif
