#ifndef __LEXER_HPP
#define __LEXER_HPP

#include "StateMachine.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
    class Lexer{
    private:
      StateMachine *machine;
    public:
      Lexer();      
    };
    }
  }
}

#endif
