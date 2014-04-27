#ifndef __MAPFILEPARSER2_HPP
#define __MAPFILEPARSER2_HPP

#include <vector>
#include <cstring>
#include <cstdlib> 
#include <map>
#include "../../GameMap.hpp"
#include "../../engine/object/Model.hpp"
#include "SyntaxConstraintFactory.hpp"
#include "SyntaxConstraint.hpp"
#include "EventType.hpp"
#include "ParserState.hpp"

using namespace glPortal::engine::object;

namespace glPortal {
  namespace map{
    namespace parser{
    class MapFileParser2{
    private:
      std::map<std::string, std::vector<SyntaxConstraint> > characterConstraints;
      std::map<std::string, std::vector<SyntaxConstraint> > characterConstraintsComments;
      void executeConstraint(std::map<std::string, std::vector<SyntaxConstraint> > &constraintMap);
      std::string fileName;
      GameMap gameMap;
      GLfloat lightpos[4];
      GLfloat barrelPosition[4];
      float startpos[3];
      float cakepos[3];	
      Box cakeBox;
      ParserState state;
      int lineNumber = 0;
      std::string command, stringStack, currentCharacter;
      std::string currentPositionMessage;
      std::vector<std::string> parameters;
      void parse(std::ifstream &fileStream);
      void tokenize();
      bool skipLine = false;
      bool revertStatus = false;
      void initializeSyntax();
      void clearStringStack();
      void executeEvent(EventType event);
      void executeCurrentCommand();
      void throwException();
      std::string parserStateStrings[10] = {
        "PREVIOUS STATE",
        "INITIAL STATE","READING COMMAND","READING PARAMETERS", 
        "AWAITING TERMINATION OR ARRAY", "READING ARRAY",
        "COMMENT INDICATION", "LONG COMMENT", "COMMENT", "LONG COMMENT AWAITING TERMINATION"
      };
      const std::string NO_FILE_MESSAGE = "Unable to load map. File does not exist";
    public:
      GameMap getMapFromFile(std::string filename);
    };
    }
  }
}

#endif
