#ifndef __TREE_NODE_TYPE_HPP
#define __TREE_NODE_TYPE_HPP
namespace glPortal {
  namespace util{
    namespace parser{
      enum class TreeNodeType { 
	ROOT,
        COMMAND, 
        PARAMETER,
        END_COMMAND
      };
    }
  }
}
#endif
