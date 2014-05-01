#ifndef __SYNTAX_CONSTRAINT_FACTORY_HPP
#define __SYNTAX_CONSTRAINT_FACTORY_HPP
#include <vector>
#include <map>
#include <string>
#include "SyntaxConstraint.hpp"
#include "EventType.hpp"
#include "ParserState.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
      typedef std::map<std::string, std::vector<SyntaxConstraint> > CharacterConstraintMap;
      class SyntaxConstraintFactory {
      public:
        static std::map<std::string, std::vector<SyntaxConstraint> > getCLikeCharacterMap();
        static std::map<std::string, std::vector<SyntaxConstraint> > getCLikeCharacterMapComment();
        static std::map<std::string, std::vector<SyntaxConstraint> > getCLikeCharacterMapArray();
      };
    }
  }
}
#endif
