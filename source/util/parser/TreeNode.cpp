#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      TreeNode::TreeNode(TreeNodeType type, std::string content){
        this->type    = type;
        this->content = content;
      }
      
      std::string TreeNode::getContent(){
        return this->content;
      }

      TreeNodeType TreeNode::getType(){
        return this->type;
      }

      void TreeNode::setParent(TreeNode *node){
	this->parent = node;
      }

      TreeNode *TreeNode::getParent(){
	return this->parent;
      }

      bool TreeNode::hasParent(){
	if(this->parent){
	  return true;
	}
	return false;
      }

      void TreeNode::addChild(TreeNode *child){
	child->setParent(this);
        this->children.push_back(child);
      }
      
      std::vector<TreeNode *> TreeNode::getChildren(){
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
