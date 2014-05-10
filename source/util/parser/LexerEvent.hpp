#ifndef __LEXER_EVENT_HPP
#define __LEXER_EVENT_HPP
namespace glPortal {
  namespace util{
    namespace parser{
      enum class LexerEvent { 
        COMMAND, 
        PARAMETER,
        NOTHING,
        END_COMMAND
      };
    }
  }
}
#endif
