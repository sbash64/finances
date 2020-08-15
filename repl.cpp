#include "repl.hpp"
#include <finances/Presenter.hpp>
#include <finances/CommandResponder.hpp>
#include <finances/FormattedWriter.hpp>
#include <finances/ItemizedFormatter.hpp>
#include <finances/TransactionRecord.hpp>
#include <gsl/gsl>
#include <iostream>

namespace finances {
namespace {
class ConsoleWriter : public Writer {
  public:
    void write(const std::string &s) override { std::cout << s; }
};
}

[[noreturn]] void repl(Input &input) {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    Presenter presenter{formattedWriter};
    TransactionRecord record{presenter};
    CommandResponder responder{record, formattedWriter};
    Prompt prompt{input, responder};
    for (;;)
        prompt.once();
}
}
