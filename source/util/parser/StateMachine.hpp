#ifndef __STATE_MACHINE_HPP
#define __STATE_MACHINE_HPP

#include <string>
#include <map>
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"
#include "StateMachineChangeSet.hpp"
#include "SyntaxConstraint.hpp"

typedef std::map<MachineState, glPortal::util::parser::StateMachineChangeSet> MachineStateChangeSetMap;

namespace glPortal {
  namespace util{
    namespace parser{
      class StateMachine{
      private:
	std::map<std::string, MachineStateChangeSetMap> constraintMap;
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
