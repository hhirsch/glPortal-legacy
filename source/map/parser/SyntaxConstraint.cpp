#include "SyntaxConstraint.hpp"
#include <vector>
#include "EventType.hpp"
#include "ParserState.hpp"
#include <iostream>

namespace glPortal {
  namespace map{
    namespace parser{
      void SyntaxConstraint::addEvent(EventType event){
        events.push_back(event);
      }

      void SyntaxConstraint::addPrerequisiteState(ParserState state){
        prerequisiteStates.push_back(state);
      }

      void SyntaxConstraint::setResultState(ParserState state){
        resultState = state;
      }

      ParserState SyntaxConstraint::getResultState(){
        return resultState;
      }

      std::vector<EventType> SyntaxConstraint::getEvents() {
        return events;
      }

      bool SyntaxConstraint::getIsValidPrerequisiteState(ParserState &state){
        for(std::vector<ParserState>::iterator preState = prerequisiteStates.begin(); preState != prerequisiteStates.end(); ++preState) {
          if(state == *preState){
            return true;
          }
        }
        return false;
      }
    }
  }
}
