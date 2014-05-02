#include "ParseTreeNode.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      ParseTreeNode::ParseTreeNode(std::string content){
        this->content = content;
      }
      
      void ParseTreeNode::addChild(ParseTreeNode child){
        this->children.push_back(child);
      }
    }
  }
}
