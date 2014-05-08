#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>      
#include "Lexer.hpp"
#include "StateMachine.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      Parser::Parser(std::string filename):  rootNode("root"){
        this->filename = filename;
        this->fileStream = new std::ifstream(filename, std::ifstream::in);

        if(!fileStream){
          throw std::invalid_argument("File " + filename + " not found.");
        }
      
      }

      void Parser::generateTree(){
        while(fileStream->good()) {
          //state = ParserState::READING_COMMAND;
          //          this->parse(fileStream);
          fileStream->close();
        }
      }

      TreeNode* Parser::getRootNode(){
        return &rootNode;
      }
    }
  }
}
