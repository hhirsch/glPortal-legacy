#include "SyntaxConstraint.hpp"
#include <vector>
#include "EventType.hpp"
#include "ParserState.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      void SyntaxConstraint::addEvent(EventType event){
        events.push_back(event);
      }

      void SyntaxConstraint::addPrerequisiteState(ParserState state){
        prerequisiteState.push_back(state);
      }

      void SyntaxConstraint::setResultState(ParserState state){
        resultState = state;
      }

      std::vector<EventType> SyntaxConstraint::getEvents() {
        return events;
      }
    }
  }
}
