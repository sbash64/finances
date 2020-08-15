#ifndef FINANCES_INCLUDE_FINANCES_PROMPT_HPP_
#define FINANCES_INCLUDE_FINANCES_PROMPT_HPP_

#include "Responder.hpp"
#include <string>

namespace finances {
class Input {
  public:
    virtual ~Input() = default;
    virtual auto next(const std::string &prompt) -> std::string = 0;
};

class Prompt {
  public:
    Prompt(
        Input &, Responder &, std::string primary = "$ ", std::string = "> ");

    void once();

  private:
    Input &input;
    Responder &responder;
    std::string primary;
    std::string secondary;
};
}

#endif
