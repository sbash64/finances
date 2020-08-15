#include <sbash64/finances/Presenter.hpp>
#include <sbash64/finances/CommandResponder.hpp>
#include <sbash64/finances/FormattedWriter.hpp>
#include <sbash64/finances/ItemizedFormatter.hpp>
#include <sbash64/finances/TransactionRecord.hpp>
#include <sbash64/finances/Prompt.hpp>
#include <readline/readline.h>
#include <readline/history.h>
#include <gsl/gsl>
#include <iostream>

namespace finances {
namespace {
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
    gsl::owner<char *> line;
};

auto cString(const Readline &line) -> const char * { return line.cString(); }

class ReadlineInput : public Input {
  public:
    auto next(const std::string &prompt) -> std::string override {
        Readline line{prompt};
        if (cString(line) != nullptr && *cString(line) != 0)
            add_history(cString(line));
        return cString(line);
    }
};

class ConsoleWriter : public Writer {
  public:
    void write(const std::string &s) override { std::cout << s; }
};

[[noreturn]] void main() {
    ConsoleWriter writer;
    ItemizedFormatter formatter;
    FormattedWriter formattedWriter{formatter, writer};
    Presenter presenter{formattedWriter};
    TransactionRecord record{presenter};
    CommandResponder responder{record, formattedWriter};
    ReadlineInput input;
    Prompt prompt{input, responder};
    for (;;)
        prompt.once();
}
}
}

int main() { finances::main(); }
