#include "PromptTests.hpp"
#include <sbash64/finances/Prompt.hpp>
#include <functional>
#include <utility>

namespace sbash64::finances {
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

    void setPrompt(std::string s, Prompt::Level level = {}) {
        static_cast<std::string &>(prompt_) = std::move(s);
        prompt_.level = level;
    }

    auto prompt() -> Prompt override { return prompt_; }

  private:
    std::string entered_;
    Prompt prompt_;
};

void assertPromptEquals(sbash64::testcpplite::TestResult &result, InputStub &input,
    const std::string &what) {
    assertEqual(result, what, input.prompt());
}

void testPrompt(
    const std::function<void(Prompt &, InputStub &, ResponderStub &)> &f,
    std::string primary = {}, std::string secondary = {}) {
    InputStub input;
    ResponderStub responder;
    Prompt prompt{input, responder, std::move(primary), std::move(secondary)};
    f(prompt, input, responder);
}
}

void promptPassesInputToResponder(sbash64::testcpplite::TestResult &result) {
    testPrompt([&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
        input.setNext("a");
        prompt.once();
        assertEqual(result, "a", responder.entered());
    });
}

void promptCombinesPrimaryPromptForInput(sbash64::testcpplite::TestResult &result) {
    testPrompt(
        [&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
            responder.setPrompt("a");
            prompt.once();
            assertPromptEquals(result, input, "a$ ");
        },
        "$ ");
}

void promptCombinesSecondaryPromptForInput(sbash64::testcpplite::TestResult &result) {
    testPrompt(
        [&](Prompt &prompt, InputStub &input, ResponderStub &responder) {
            responder.setPrompt("a", Responder::Prompt::Level::secondary);
            prompt.once();
            assertPromptEquals(result, input, "a> ");
        },
        "$ ", "> ");
}
}
