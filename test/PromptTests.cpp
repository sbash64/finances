#include "PromptTests.hpp"
#include <finances/Prompt.hpp>
#include <functional>

namespace finances {
namespace {
class InputStub : public Input {
  public:
    void setNext(std::string s) { next_ = std::move(s); }

    auto next(const std::string &s) -> std::string override {
        prompt_ = s;
        return next_;
    }

    auto prompt() -> std::string { return prompt_; }

  private:
    std::string next_;
    std::string prompt_;
};

class ResponderStub : public Responder {
  public:
    auto entered() -> std::string { return entered_; }

    void enter(const std::string &s) override { entered_ = s; }

    void setPrompt(std::string s) { prompt_ = std::move(s); }

    auto prompt() -> std::string override { return prompt_; }

    void setSecondary() { secondary_ = true; }

    auto secondary() -> bool { return secondary_; }

  private:
    std::string entered_;
    std::string prompt_;
    bool secondary_{};
};

void testPrompt(
    const std::function<void(Prompt &, InputStub &, ResponderStub &)> &f,
    std::string primary = {}, std::string secondary = {}) {
    InputStub input;
    ResponderStub responder;
    Prompt prompt{input, responder, std::move(primary), std::move(secondary)};
    f(prompt, input, responder);
}
}

void promptPassesInputToResponder(testcpplite::TestResult &result) {
    testPrompt([&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
        input.setNext("a");
        prompt.once();
        assertEqual(result, "a", responder.entered());
    });
}

void promptCombinesPrimaryPromptForInput(testcpplite::TestResult &result) {
    testPrompt(
        [&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
            responder.setPrompt("a");
            prompt.once();
            assertEqual(result, "a$ ", input.prompt());
        },
        "$ ", "> ");
}

void promptCombinesSecondaryPromptForInput(testcpplite::TestResult &result) {
    testPrompt(
        [&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
            responder.setPrompt("a");
            responder.setSecondary();
            prompt.once();
            assertEqual(result, "a> ", input.prompt());
        },
        "$ ", "> ");
}
}
