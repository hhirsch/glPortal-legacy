#include "ParseTreeNode.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      ParseTreeNode::ParseTreeNode(std::string command){
        this->command = command;
      }
      
      void ParseTreeNode::addParameter(std::string parameter){
        this->parameters.push_back(parameter);
      }
    }
  }
}
