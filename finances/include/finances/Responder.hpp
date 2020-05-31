#ifndef FINANCES_INCLUDE_FINANCES_RESPONDER_HPP_
#define FINANCES_INCLUDE_FINANCES_RESPONDER_HPP_

#include <string>

namespace finances {
class Responder {
  public:
    virtual ~Responder() = default;
    virtual void enter(const std::string &) = 0;
};
}

#endif
