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

#include "PromptTests.hpp"

namespace finances {
namespace {
class InputStub : public Input {
  public:
    void setNext(std::string s) { next_ = std::move(s); }

    auto next() -> std::string { return next_; }

  private:
    std::string next_;
};

class ResponderStub : public Responder {
  public:
    auto entered() -> std::string { return entered_; }

    void enter(const std::string &s) { entered_ = s; }

  private:
    std::string entered_;
};
}
void promptPassesInputToResponder(testcpplite::TestResult &result) {
    InputStub input;
    ResponderStub responder;
    Prompt prompt{input, responder};
    input.setNext("a");
    prompt.once();
    assertEqual(result, "a", responder.entered());
}
}
