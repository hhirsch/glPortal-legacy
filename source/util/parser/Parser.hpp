#ifndef __PARSER_HPP
#define __PARSER_HPP

#include "TreeNode.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class Parser{
    private:
      TreeNode rootNode = TreeNode("root");
    public:
      Parser(std::string filename);
      TreeNode * getRootNode();
    };
    }
  }
}

#endif
