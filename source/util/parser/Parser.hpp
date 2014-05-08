#ifndef __PARSER_HPP
#define __PARSER_HPP

#include <sstream>
#include <string>
#include <iostream>
#include <fstream>
#include "Lexer.hpp"
#include "StateMachine.hpp"
#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class Parser{
    private:
      std::string filename;
      std::ifstream *fileStream;
      Lexer *lexer;
      StateMachine *stateMachine;
      TreeNode rootNode;
    public:
      Parser(std::string filename);
      void generateTree();
      TreeNode * getRootNode();
    };
    }
  }
}

#endif
