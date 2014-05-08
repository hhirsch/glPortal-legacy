#include "MapFileParser2.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../engine/Environment.hpp"
#include "../../Exception.hpp"
#include "../../util/parser/Parser.hpp"
#include "../../util/parser/TreeNode.hpp"
#include "MapConverter.hpp"
using namespace glPortal::util::parser;

namespace glPortal {
  namespace map{
    namespace parser{
      /**
       * Get a map from a map file.
       *
       * @param filename Path to the map file
       */
      GameMap MapFileParser2::getMapFromFile(std::string filename) {
        Parser parser = Parser(filename);
        parser.generateTree();
        cout << "parse and exit";
        exit(0);
        return MapConverter::treeNodeToGameMap(parser.getRootNode());
      }      
    }
  }
}
