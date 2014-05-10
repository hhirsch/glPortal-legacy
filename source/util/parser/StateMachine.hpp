#ifndef __STATEMACHINE_HPP
#define __STATEMACHINE_HPP

#include <string>
#include "EventType.hpp"
#include "MachineState.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class StateMachine{
    private:
      MachineState state;
      std::string stringStack, currentCharacter;
    public:
      void setState(MachineState state);
      MachineState getState();
    };
    }
  }
}

#endif
