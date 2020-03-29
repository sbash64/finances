#include <finances/Presenter.hpp>
#include <finances/FormattedWriter.hpp>
#include <finances/ItemizedFormatter.hpp>
#include <finances/TransactionRecord.hpp>
#include <readline/readline.h>
#include <iostream>

namespace finances {
namespace {
class ConsoleWriter : public Writer {
  public:
    void write(const std::string &s) override { std::cout << s; }
};

[[noreturn]] void main() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    TransactionRecord record;
    Presenter presenter{record, formattedWriter};
    while (true)
        presenter.execute(readline(nullptr));
}
}
}

int main() { finances::main(); }
