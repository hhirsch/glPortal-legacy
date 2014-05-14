#include "Scanner.hpp"
#include <sstream>

namespace glPortal {
  namespace util{
    namespace parser{
      Scanner::Scanner(Parser *parser){
	this->parser = parser;
      }

      void Scanner::scan(std::string line){
	std::string currentCharacter;
	if(line.length() > 0) {
	  for(int i = 0; i <= line.length(); i++){
	    std::stringstream conversionStream;
	    conversionStream << line[i];
	    if(line[i] == ' '){
	      currentCharacter = std::string("whitespace");
	    } else {
	      conversionStream >> currentCharacter;
	    }
	    //this->tokenize();
	  }
	}
      }

    }
  }
}
