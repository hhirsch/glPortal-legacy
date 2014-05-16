#ifndef __SCANNER_HPP
#define __SCANNER_HPP

#include <string>
#include "EventType.hpp"
#include "MachineState.hpp"
#include "StateMachine.hpp"
#include "TreeNode.hpp"
#include "Parser.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class Parser;
      class Scanner{
      private:
	Parser *parser;
	StateMachine *stateMachine;
	MachineState state;
	std::string stringStack, currentCharacter;
      public:
	Scanner(Parser *parser);
	void scan(std::string line);
	void evaluate(std::string character);
	TreeNode getRootNode();
      };
    }
  }
}

#endif
