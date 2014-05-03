#include "ParseTreeNode.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      ParseTreeNode::ParseTreeNode(std::string content){
        this->content = content;
      }
      
      std::string ParseTreeNode::getContent(){
        return this->content;
      }

      void ParseTreeNode::addChild(ParseTreeNode child){
        this->children.push_back(child);
      }
      
      std::vector<ParseTreeNode> ParseTreeNode::getChildren(){
        return this->children;
      }

      bool ParseTreeNode::isLeaf(){
        if(this->children.size() <= 0){
          return true;
        }
        return false;
      }
    }
  }
}
