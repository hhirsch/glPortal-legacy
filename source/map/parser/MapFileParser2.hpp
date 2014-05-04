#ifndef __MAPFILEPARSER2_HPP
#define __MAPFILEPARSER2_HPP

#include <vector>
#include <cstring>
#include <cstdlib> 
#include <map>
#include "../../GameMap.hpp"
using namespace glPortal::engine::object;

namespace glPortal {
  namespace map{
    namespace parser{
    class MapFileParser2{
    private:
    public:
      GameMap getMapFromFile(std::string filename);
    };
    }
  }
}

#endif
