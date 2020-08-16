#ifndef FINANCES_INCLUDE_FINANCES_RESPONDER_HPP_
#define FINANCES_INCLUDE_FINANCES_RESPONDER_HPP_

#include <string>
#include <utility>

namespace sbash64::finances {
class Responder {
  public:
    struct Prompt : std::string {
        enum class Level { primary, secondary };
        explicit Prompt(std::string s = {}, Level level = {})
            : std::string{std::move(s)}, level{level} {}
        Level level;
    };
    virtual ~Responder() = default;
    virtual void enter(const std::string &) = 0;
    virtual auto prompt() -> Prompt = 0;
};
}

#endif
