#include "SyntaxConstraint.hpp"
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"
#include <iostream>

namespace glPortal {
  namespace util{
    namespace parser{
      void SyntaxConstraint::addEvent(EventType event){
        events.push_back(event);
      }

      void SyntaxConstraint::addPrerequisiteState(MachineState state){
        prerequisiteStates.push_back(state);
      }

      void SyntaxConstraint::setResultState(MachineState state){
        resultState = state;
      }

      MachineState SyntaxConstraint::getResultState(){
        return resultState;
      }

      std::vector<EventType> SyntaxConstraint::getEvents() {
        return events;
      }

      bool SyntaxConstraint::getIsValidPrerequisiteState(MachineState &state){
        for(std::vector<MachineState>::iterator preState = prerequisiteStates.begin(); preState != prerequisiteStates.end(); ++preState) {
          if(state == *preState){
            return true;
          }
        }
        return false;
      }
    }
  }
}
