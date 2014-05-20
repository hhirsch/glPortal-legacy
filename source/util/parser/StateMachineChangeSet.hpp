#ifndef __STATE_MACHINE_CHANGE_SET_HPP
#define __STATE_MACHINE_CHANGE_SET_HPP
#include <vector>
#include "EventType.hpp"
#include "MachineState.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class StateMachineChangeSet {
      public:
	StateMachineChangeSet();
        void addEvent(EventType event);
        void setResultState(MachineState state);
        MachineState getResultState();
        std::vector<EventType> getEvents();
      private:
        std::vector<EventType> events;
        MachineState resultState;
      };
    }
  }
}
#endif
