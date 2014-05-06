#include "Parser.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      Parser::Parser(std::string filename){
      }

      TreeNode* Parser::getRootNode(){
        return &rootNode;
      }
    }
  }
}
