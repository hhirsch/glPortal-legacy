#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      TreeNode::TreeNode(std::string content){
        this->content = content;
      }
      
      std::string TreeNode::getContent(){
        return this->content;
      }

      void TreeNode::addChild(TreeNode child){
        this->children.push_back(child);
      }
      
      std::vector<TreeNode> TreeNode::getChildren(){
        return this->children;
      }

      bool TreeNode::isLeaf(){
        if(this->children.size() <= 0){
          return true;
        }
        return false;
      }
    }
  }
}
