#include "repl.hpp"
#include <iostream>
#include <string>

namespace {
class GetlineInput : public sbash64::finances::Input {
  public:
    auto next(const std::string &prompt) -> std::string override {
        std::cout << prompt;
        std::string next;
        std::getline(std::cin, next);
        return next;
    }
};
}

int main() {
    GetlineInput input;
    sbash64::finances::repl(input);
}
