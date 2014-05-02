#ifndef __STATEMACHINE_HPP
#define __STATEMACHINE_HPP

#include <string>
#include "EventType.hpp"
#include "ParserState.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
    class StateMachine{
    private:
      ParserState state;
      std::string stringStack, currentCharacter;
    public:
    };
    }
  }
}

#endif
