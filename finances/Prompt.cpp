#include "Prompt.hpp"

namespace finances {
Prompt::Prompt(Input &input, Responder &responder)
    : input{input}, responder{responder} {}

void Prompt::once() { responder.enter(input.next()); }
}
