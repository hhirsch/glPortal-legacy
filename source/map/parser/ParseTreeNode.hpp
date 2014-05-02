#ifndef __PARSETREENODE_HPP
#define __PARSETREENODE_HPP

#include <string>
#include <vector>

namespace glPortal {
  namespace map{
    namespace parser{
    class ParseTreeNode{
    private:
      std::string command;
      std::vector<std::string> parameters;
    public:
      ParseTreeNode(std::string command);
      void addParameter(std::string parameter);
    };
    }
  }
}

#endif
