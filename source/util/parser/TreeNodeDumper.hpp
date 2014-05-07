#ifndef __TREENODE_DUMPER_HPP
#define __TREENODE_DUMPER_HPP

#include <string>
#include <vector>
#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class TreeNodeDumper{
    private:
      TreeNode *node;
    public:
      TreeNodeDumper(TreeNode *node);
      void dumpAll(std::string content);
      void dumpAllByContent(std::string content);
    };
    }
  }
}

#endif
