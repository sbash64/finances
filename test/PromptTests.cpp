#include "PromptTests.hpp"
#include <finances/Prompt.hpp>

namespace finances {
namespace {
class InputStub : public Input {
  public:
    void setNext(std::string s) { next_ = std::move(s); }

    auto next() -> std::string override { return next_; }

  private:
    std::string next_;
};

class ResponderStub : public Responder {
  public:
    auto entered() -> std::string { return entered_; }

    void enter(const std::string &s) override { entered_ = s; }

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
