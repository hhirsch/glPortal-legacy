#include "StateMachineChangeSet.hpp"
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"
#include <iostream>

namespace glPortal {
  namespace util{
    namespace parser{
      StateMachineChangeSet::StateMachineChangeSet(): resultState(MachineState::INITIAL_STATE){
      }
      void StateMachineChangeSet::addEvent(EventType event){
        events.push_back(event);
      }

      void StateMachineChangeSet::setResultState(MachineState state){
        resultState = state;
      }

      MachineState StateMachineChangeSet::getResultState(){
        return resultState;
      }

      std::vector<EventType> StateMachineChangeSet::getEvents() {
        return events;
      }
    }
  }
}
