#ifndef FINANCES_INCLUDE_FINANCES_PROMPT_HPP_
#define FINANCES_INCLUDE_FINANCES_PROMPT_HPP_

#include "Responder.hpp"
#include <string>

namespace finances {
class Input {
  public:
    virtual ~Input() = default;
    virtual auto next() -> std::string = 0;
};

class Prompt {
  public:
    Prompt(Input &, Responder &);

    void once();

  private:
    Input &input;
    Responder &responder;
};
}

#endif
