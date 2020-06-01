#include "Prompt.hpp"

namespace finances {
Prompt::Prompt(Input &input, Responder &responder, std::string primary,
    std::string secondary)
    : input{input}, responder{responder}, primary{std::move(primary)},
      secondary{std::move(secondary)} {}

void Prompt::once() {
    responder.enter(input.next(responder.prompt() + primary));
}
}
