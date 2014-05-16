#ifndef __STATE_MACHINE_HPP
#define __STATE_MACHINE_HPP

#include <string>
#include <map>
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"
#include "SyntaxConstraint.hpp"

typedef std::map<std::string, glPortal::util::parser::SyntaxConstraint> CharacterConstraintMap;

namespace glPortal {
  namespace util{
    namespace parser{
      class StateMachine{
      private:
	std::map<MachineState, CharacterConstraintMap> stateConstraintMap;
	MachineState state;
	std::string stringStack, currentCharacter;
      public:
      void setCharacter(std::string character);
	std::vector<EventType> getEvents();
      };
    }
  }
}

#endif
