#ifndef FINANCES_INCLUDE_FINANCES_PROMPT_HPP_
#define FINANCES_INCLUDE_FINANCES_PROMPT_HPP_

#include <string>

namespace finances {
class Input {
  public:
    virtual ~Input() = default;
    virtual auto next() -> std::string = 0;
};

class Responder {
  public:
    virtual ~Responder() = default;
    virtual void enter(const std::string &) = 0;
};

class Prompt {
  public:
    Prompt(Input &input, Responder &responder)
        : input{input}, responder{responder} {}

    void once() { responder.enter(input.next()); }

  private:
    Input &input;
    Responder &responder;
};
}

#endif
