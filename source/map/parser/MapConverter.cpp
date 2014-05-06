#include "MapConverter.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      GameMap MapConverter::treeNodeToGameMap(TreeNode *node){
        GameMap *map = new GameMap();
        return *map;
      }
    }
  }
}
