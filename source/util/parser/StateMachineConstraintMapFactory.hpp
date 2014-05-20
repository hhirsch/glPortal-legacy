#ifndef __STATE_MACHINE_CONSTRAINT_MAP_FACTORY_HPP
#define __STATE_MACHINE_CONSTRAINT_MAP_FACTORY_HPP
#include <map>
#include <string>
#include "EventType.hpp"
#include "StateMachine.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class StateMachineConstraintMapFactory {
      public:
	static std::map<std::string, MachineStateChangeSetMap> getConstraintMap();
      };
    }
  }
}
#endif
