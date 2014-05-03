#ifndef __PARSETREENODE_HPP
#define __PARSETREENODE_HPP

#include <string>
#include <vector>

namespace glPortal {
  namespace map{
    namespace parser{
    class ParseTreeNode{
    private:
      std::string content;
      std::vector<ParseTreeNode> children;
    public:
      ParseTreeNode(std::string content);
      std::string getContent();
      std::vector<ParseTreeNode> getChildren();
      void addChild(ParseTreeNode child);      
      bool isLeaf();
    };
    }
  }
}

#endif
