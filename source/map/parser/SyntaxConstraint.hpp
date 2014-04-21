#ifndef __SYNTAX_CONSTRAINT_HPP
#define __SYNTAX_CONSTRAINT_HPP
#include <vector>
#include "EventType.hpp"
#include "ParserState.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      class SyntaxConstraint {
      public:
        void addEvent(EventType event);
        void addPrerequisiteState(ParserState state);
        void setResultState(ParserState state);
      private:
        std::vector<EventType> events;
        std::vector<ParserState> prerequisiteState;
        ParserState resultState;
        std::vector<EventType> getEvents();
      };
    }
  }
}
#endif
