#ifndef __SYNTAX_CONSTRAINT_HPP
#define __SYNTAX_CONSTRAINT_HPP
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class SyntaxConstraint {
      public:
        void addEvent(EventType event);
        void addPrerequisiteState(MachineState state);
        void setResultState(MachineState state);
        MachineState getResultState();
        bool getIsValidPrerequisiteState(MachineState &state);
        std::vector<EventType> getEvents();
      private:
        std::vector<EventType> events;
        std::vector<MachineState> prerequisiteStates;
        MachineState resultState;
      };
    }
  }
}
#endif
