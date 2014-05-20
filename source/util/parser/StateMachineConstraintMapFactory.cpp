#include "StateMachineConstraintMapFactory.hpp"
#include "StateMachineChangeSet.hpp"
#include <vector>
#include <map>
#include <string>
#include "EventType.hpp"
#include "MachineState.hpp"
#include <iostream>

namespace glPortal {
  namespace util{
    namespace parser{
	typedef std::map<std::string, std::string> StringMap;
      std::map<std::string, MachineStateChangeSetMap> StateMachineConstraintMapFactory::getConstraintMap(){
	std::map<std::string, MachineStateChangeSetMap> constraintMap;
	StateMachineChangeSet changeSet;
	changeSet.setResultState(MachineState::READING_COMMAND);
	MachineStateChangeSetMap changeSetMap;
	changeSetMap[MachineState::READING_COMMAND] =  changeSet;
	constraintMap[std::string("(")] = changeSetMap;

	return constraintMap;
      }
    }
  }
}
