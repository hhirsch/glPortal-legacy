#include "StateMachine.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      void StateMachine::setCharacter(std::string character){
	this->currentCharacter = character;
      }
      
      std::vector<EventType> StateMachine::getEvents(){
        if((constraintMap.find(currentCharacter) != constraintMap.end())){
	  MachineStateChangeSetMap machineStateChangeSetMap =  constraintMap.at(currentCharacter);
	  if((machineStateChangeSetMap.find(state) != machineStateChangeSetMap.end())){
	    StateMachineChangeSet changeSet =  machineStateChangeSetMap.at(state);
	    
	  }
	}
      }
    }
  }
}
