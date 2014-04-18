#ifndef __MAPFILEPARSER2_HPP
#define __MAPFILEPARSER2_HPP

#include <vector>
#include <cstring>
#include <cstdlib> 
#include "../GameMap.hpp"
#include "../engine/object/Model.hpp"

using namespace glPortal::engine::object;

enum PARSER_STATE { 
PARSER_INITIAL_STATE,
PARSER_READING_COMMAND, 
PARSER_READING_PARAMETERS, 
PARSER_WAITING_TERMINATION 
};

namespace glPortal {
  namespace map{
    class MapFileParser2{
    private:
      std::string fileName;
      GameMap gameMap;
      GLfloat lightpos[4];
      GLfloat barrelPosition[4];
      float startpos[3];
      float cakepos[3];	
      Box cakeBox;
      PARSER_STATE state;
      int lineNumber = 0;
      std::string stringStack, currentCharacter;;
      std::string currentPositionMessage;
      std::vector<std::string> parameters;
      void parse(std::ifstream &fileStream);
      void tokenize();
      void throwException();
      std::string parserStateStrings[4] = {
        "INITIAL STATE","READING COMMAND","READING PARAMETERS", "AWAITING TERMINATION"
      };
      const std::string NO_FILE_MESSAGE = "Unable to load map. File does not exist";
    public:
      GameMap getMapFromFile(std::string filename);
    };
  }
}

#endif
