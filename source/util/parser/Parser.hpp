#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Lexer.hpp"
#include "LexerEvent.hpp"
#include "Scanner.hpp"
#include "StateMachine.hpp"
#include "TreeNode.hpp"
#include "TreeNodeType.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      class Scanner;
      class Parser{
      private:
	std::string filename;
	int lineNumber;
      std::ifstream *fileStream;
	Lexer *lexer;
	Scanner *scanner;
	LexerEvent lastEvent;
	StateMachine *stateMachine;
	TreeNode *rootNode;
	TreeNode *currentCommand;
      public:
	Parser(std::string filename);
	void addNode(LexerEvent event, std::string data);
	void parse(std::ifstream &fileStream);
	void generateTree();
      TreeNode * getRootNode();
      };
    }
  }
}

#endif
