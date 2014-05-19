#include "StateMachineConstraintMapFactory.hpp"
#include <vector>
#include <map>
#include "EventType.hpp"
#include "ParserState.hpp"
#include <iostream>

namespace glPortal {
  namespace map{
    namespace parser{
      std::map<std::string, MachineStateChangeSetMap> StateMachineConstraintMapFactory::getConstraintMap(){
	std::map<std::string, MachineStateChangeSetMap> constraintMap;
	return constraintMap;
      }
    }
  }
}
