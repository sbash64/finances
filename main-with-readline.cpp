#include "repl.hpp"
#include <readline/readline.h>
#include <readline/history.h>
#include <gsl/gsl>

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

class ReadlineInput : public finances::Input {
  public:
    auto next(const std::string &prompt) -> std::string override {
        Readline line{prompt};
        if (cString(line) != nullptr && *cString(line) != 0)
            add_history(cString(line));
        return cString(line);
    }
};
}

int main() {
    ReadlineInput readlineInput;
    finances::repl(readlineInput);
}
