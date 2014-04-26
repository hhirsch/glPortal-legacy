#include "SyntaxConstraintFactory.hpp"
#include <vector>
#include <map>
#include "EventType.hpp"
#include "ParserState.hpp"
#include <iostream>

namespace glPortal {
  namespace map{
    namespace parser{
      std::map<std::string, std::vector<SyntaxConstraint> > SyntaxConstraintFactory::getCLikeCharacterMap(){
        std::map<std::string, std::vector<SyntaxConstraint> > characterConstraints;
        SyntaxConstraint brace, closingBrace, comma, 
          semicolon, curlyBrace, closingCurlyBrace,
          commentInit, comment, longComment, longCommentClose;
        brace.addPrerequisiteState(ParserState::READING_COMMAND);
        brace.setResultState(ParserState::READING_PARAMETERS);
        brace.addEvent(EventType::COPY_BUFFER_TO_COMMAND);
        brace.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> braceVector;
        braceVector.push_back(brace);
        characterConstraints["("] = braceVector;

        closingBrace.addPrerequisiteState(ParserState::READING_PARAMETERS);
        closingBrace.setResultState(ParserState::WAITING_TERMINATION);
        closingBrace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        closingBrace.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> closingBraceVector;
        closingBraceVector.push_back(closingBrace);
        characterConstraints[")"] = closingBraceVector;

        comma.addPrerequisiteState(ParserState::READING_PARAMETERS);
        comma.addPrerequisiteState(ParserState::READING_ARRAY);
        comma.setResultState(ParserState::PREVIOUS_STATE);
        comma.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        comma.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> commaVector;
        commaVector.push_back(comma);
        characterConstraints[","] = commaVector;

        semicolon.addPrerequisiteState(ParserState::WAITING_TERMINATION);
        semicolon.setResultState(ParserState::READING_COMMAND);
        semicolon.addEvent(EventType::CLEAR_BUFFER);
        semicolon.addEvent(EventType::EXECUTE);
        std::vector<SyntaxConstraint> semicolonVector;
        semicolonVector.push_back(semicolon);
        characterConstraints[";"] = semicolonVector;

        curlyBrace.addPrerequisiteState(ParserState::WAITING_TERMINATION);
        curlyBrace.setResultState(ParserState::READING_ARRAY);
        std::vector<SyntaxConstraint> curlyBraceVector;
        curlyBraceVector.push_back(curlyBrace);
        characterConstraints["{"] = curlyBraceVector;

        closingCurlyBrace.addPrerequisiteState(ParserState::READING_ARRAY);
        closingCurlyBrace.setResultState(ParserState::READING_COMMAND);
        closingCurlyBrace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        closingCurlyBrace.addEvent(EventType::CLEAR_BUFFER);
        closingCurlyBrace.addEvent(EventType::EXECUTE);
        std::vector<SyntaxConstraint> closingCurlyBraceVector;
        closingCurlyBraceVector.push_back(closingCurlyBrace);
        characterConstraints["}"] = closingCurlyBraceVector;
        
        commentInit.addPrerequisiteState(ParserState::READING_COMMAND);
        commentInit.setResultState(ParserState::WAITING_COMMENT);
        comment.addPrerequisiteState(ParserState::WAITING_COMMENT);
        comment.setResultState(ParserState::COMMENT);
        comment.addEvent(EventType::IGNORE_LINE);
        std::vector<SyntaxConstraint> commentInitVector;
        commentInitVector.push_back(commentInit);
        commentInitVector.push_back(comment);
        characterConstraints["/"] = commentInitVector; 
        
        longComment.addPrerequisiteState(ParserState::WAITING_COMMENT);
        longComment.setResultState(ParserState::LONG_COMMENT);
        longComment.addEvent(EventType::IGNORE);
        std::vector<SyntaxConstraint> longCommentVector;
        longCommentClose.addPrerequisiteState(ParserState::LONG_COMMENT);
        longCommentClose.setResultState(ParserState::READING_COMMAND);
        longComment.addEvent(EventType::IGNORE_END);
        longCommentVector.push_back(longComment);
        longCommentVector.push_back(longCommentClose);
        characterConstraints["*"] = longCommentVector;

        return characterConstraints;
      }
    }
  }
}
