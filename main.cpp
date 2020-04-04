#include <finances/Presenter.hpp>
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

    auto c_str() const -> const char * { return line; }

  private:
    char *line;
};

auto c_str(const Readline &line) -> const char * { return line.c_str(); }

[[noreturn]] void main() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    TransactionRecord record;
    Presenter presenter{record, formattedWriter};
    for (;;) {
        Readline line("finances$ ");
        presenter.execute(c_str(line));
        if (c_str(line) != nullptr && *c_str(line) != 0)
            add_history(c_str(line));
    }
}
}
}

int main() { finances::main(); }
