#include <finances/Presenter.hpp>
#include <finances/CommandResponder.hpp>
#include <finances/FormattedWriter.hpp>
#include <finances/ItemizedFormatter.hpp>
#include <finances/TransactionRecord.hpp>
#include <readline/readline.h>
#include <readline/history.h>
#include <iostream>

namespace finances {
namespace {
class ConsoleWriter : public Writer {
  public:
    void write(const std::string &s) override { std::cout << s; }
};

class Readline {
  public:
    explicit Readline(const std::string &prompt)
        : line{readline(prompt.c_str())} {}

    ~Readline() { free(line); }

    Readline(const Readline &) = delete;
    auto operator=(const Readline &) -> Readline & = delete;
    Readline(Readline &&) noexcept = delete;
    auto operator=(Readline &&) noexcept -> Readline & = delete;

    auto cString() const -> const char * { return line; }

  private:
    char *line;
};

auto cString(const Readline &line) -> const char * { return line.cString(); }

[[noreturn]] void main() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    Presenter presenter{formattedWriter};
    TransactionRecord record{presenter};
    CommandResponder responder{record, formattedWriter};
    for (;;) {
        Readline line{"finances$ "};
        responder.enter(cString(line));
        if (cString(line) != nullptr && *cString(line) != 0)
            add_history(cString(line));
    }
}
}
}

int main() { finances::main(); }
