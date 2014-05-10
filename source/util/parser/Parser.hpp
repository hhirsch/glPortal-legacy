#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Lexer.hpp"
#include "Scanner.hpp"
#include "StateMachine.hpp"
#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class Parser{
    private:
      std::string filename;
      int lineNumber;
      std::ifstream *fileStream;
      Lexer *lexer;
      Scanner *scanner;
      StateMachine *stateMachine;
      TreeNode rootNode;
    public:
      Parser(std::string filename);
      void parse(std::ifstream &fileStream);
      void generateTree();
      TreeNode * getRootNode();
    };
    }
  }
}

#endif
