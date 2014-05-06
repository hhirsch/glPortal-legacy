#ifndef __TREENODE_HPP
#define __TREENODE_HPP

#include <string>
#include <vector>

namespace glPortal {
  namespace util{
    namespace parser{
    class TreeNode{
    private:
      std::string content;
      std::vector<TreeNode> children;
    public:
      TreeNode(std::string content);
      std::string getContent();
      std::vector<TreeNode> getChildren();
      void addChild(TreeNode child);      
      bool isLeaf();
    };
    }
  }
}

#endif
