#ifndef __SCANNER_HPP
#define __SCANNER_HPP

#include <string>
#include "EventType.hpp"
#include "MachineState.hpp"
#include "TreeNode.hpp"
#include "Parser.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class Parser;
      class Scanner{
      private:
	Parser *parser;
	MachineState state;
	std::string stringStack, currentCharacter;
      public:
	Scanner(Parser *parser);
	void scan(std::string line);
	TreeNode getRootNode();
      };
    }
  }
}

#endif
