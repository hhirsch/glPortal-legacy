#include "Parser.hpp"
#include <fstream>
#include <sstream>

namespace glPortal {
  namespace util{
    namespace parser{
      Parser::Parser(std::string filename){
        this->filename = filename;
        this->fileStream = new std::ifstream(filename, std::ifstream::in);
        //        this->fileStream =  new std::ifstream(filename, std::ifstream::in);

        //        if(!fileStream){
          //          cout << NO_FILE_MESSAGE;
        //        }
      
      }

      void Parser::generateTree(){
        //    while(fileStream.good()) {
          //state = ParserState::READING_COMMAND;
          //this->parse(fileStream);
        //          fileStream.close();
        //        }
      }

      TreeNode* Parser::getRootNode(){
        return &rootNode;
      }
    }
  }
}
