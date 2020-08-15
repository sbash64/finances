#include "Prompt.hpp"

namespace finances {
Prompt::Prompt(Input &input, Responder &responder, std::string primary,
    std::string secondary)
    : input{input}, responder{responder}, primary{std::move(primary)},
      secondary{std::move(secondary)} {}

void Prompt::once() {
    auto prompt{responder.prompt()};
    responder.enter(input.next(prompt +
        (prompt.level == Responder::Prompt::Level::secondary ? secondary
                                                             : primary)));
}
}
