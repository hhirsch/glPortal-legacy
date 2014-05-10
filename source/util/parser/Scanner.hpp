#ifndef __SCANNER_HPP
#define __SCANNER_HPP

#include <string>
#include "EventType.hpp"
#include "MachineState.hpp"
#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class Scanner{
      private:
	MachineState state;
	std::string stringStack, currentCharacter;
      public:
	void scan(std::string line);
	TreeNode getRootNode();
      };
    }
  }
}

#endif
