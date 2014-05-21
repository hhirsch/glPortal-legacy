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
      std::map<std::string, MachineStateChangeSetMap> StateMachineConstraintMapFactory::getConstraintMap(){
	std::map<std::string, MachineStateChangeSetMap> constraintMap;
	//opening brace constraint
	StateMachineChangeSet ob_changeSet;
	ob_changeSet.setResultState(MachineState::READING_PARAMETERS);
	ob_changeSet.addEvent(EventType::COPY_BUFFER_TO_COMMAND);
	ob_changeSet.addEvent(EventType::CLEAR_BUFFER);
	MachineStateChangeSetMap ob_changeSetMap;
	ob_changeSetMap[MachineState::READING_COMMAND] =  ob_changeSet;
	constraintMap[std::string("(")] = ob_changeSetMap;

	//closing brace constraint
	StateMachineChangeSet cb_changeSet;
	cb_changeSet.setResultState(MachineState::WAITING_TERMINATION);
        cb_changeSet.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        cb_changeSet.addEvent(EventType::CLEAR_BUFFER);
	MachineStateChangeSetMap cb_changeSetMap;
	cb_changeSetMap[MachineState::READING_COMMAND] =  cb_changeSet;
	constraintMap[std::string(")")] = cb_changeSetMap;

	return constraintMap;
      }
    }
  }
}
