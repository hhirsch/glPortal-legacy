#ifndef __MAP_CONVERTER_HPP
#define __MAP_CONVERTER_HPP

#include "../../util/parser/TreeNode.hpp"
#include "../../GameMap.hpp"

using namespace glPortal::util::parser;

namespace glPortal {
  namespace map{
    namespace parser{
      class MapConverter{
      private:
      public:
        static GameMap treeNodeToGameMap(TreeNode *node);
      };
    }
  }
}

#endif
