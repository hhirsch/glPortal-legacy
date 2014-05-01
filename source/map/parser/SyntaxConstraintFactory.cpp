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
        comment.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> commentInitVector;
        commentInitVector.push_back(commentInit);
        //commentInitVector.push_back(comment);
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

      std::map<std::string, std::vector<SyntaxConstraint> > SyntaxConstraintFactory::getCLikeCharacterMapComment(){
        std::map<std::string, std::vector<SyntaxConstraint> > characterConstraints;
        SyntaxConstraint longComment, longCommentClose, longCommentTermination, comment;
                
        std::vector<SyntaxConstraint> longCommentVector;
        longComment.addPrerequisiteState(ParserState::WAITING_COMMENT);
        longComment.setResultState(ParserState::LONG_COMMENT);
        longCommentClose.addPrerequisiteState(ParserState::LONG_COMMENT);
        longCommentClose.setResultState(ParserState::LONG_COMMENT_WAITING_TERMINATION);
        longCommentVector.push_back(longCommentClose);
        longCommentVector.push_back(longComment);
        characterConstraints["*"] = longCommentVector;

        longCommentTermination.addPrerequisiteState(ParserState::LONG_COMMENT_WAITING_TERMINATION);
        longCommentTermination.setResultState(ParserState::READING_COMMAND);
        longCommentTermination.addEvent(EventType::CLEAR_BUFFER);

        comment.addPrerequisiteState(ParserState::WAITING_COMMENT);
        comment.setResultState(ParserState::COMMENT);
        comment.addEvent(EventType::IGNORE_LINE);
        comment.addEvent(EventType::CLEAR_BUFFER);

        std::vector<SyntaxConstraint> longCommentTerminationVector;
        longCommentTerminationVector.push_back(longCommentTermination);
        longCommentTerminationVector.push_back(comment);
        characterConstraints["/"] = longCommentTerminationVector; 


        return characterConstraints;
      }

      std::map<std::string, std::vector<SyntaxConstraint> > SyntaxConstraintFactory::getCLikeCharacterMapArray(){
        std::map<std::string, std::vector<SyntaxConstraint> > characterConstraints;
        SyntaxConstraint array, comma, whiteSpace, brace;
                
        comma.addPrerequisiteState(ParserState::READING_PARAMETERS);
        comma.addPrerequisiteState(ParserState::READING_ARRAY);
        comma.setResultState(ParserState::PREVIOUS_STATE);
        comma.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        comma.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> commaVector;
        commaVector.push_back(comma);
        characterConstraints[","] = commaVector;
        
        whiteSpace.addPrerequisiteState(ParserState::READING_PARAMETERS);
        whiteSpace.addPrerequisiteState(ParserState::READING_ARRAY);
        whiteSpace.setResultState(ParserState::PREVIOUS_STATE);
        whiteSpace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        whiteSpace.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> whiteSpaceVector;
        commaVector.push_back(whiteSpace);
        characterConstraints["whitespace"] = whiteSpaceVector;

        brace.addPrerequisiteState(ParserState::READING_PARAMETERS);
        brace.addPrerequisiteState(ParserState::READING_ARRAY);
        brace.setResultState(ParserState::PREVIOUS_STATE);
        brace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
        brace.addEvent(EventType::CLEAR_BUFFER);
        std::vector<SyntaxConstraint> braceVector;
        braceVector.push_back(brace);
        characterConstraints[">"] = braceVector;

        return characterConstraints;
      }

    }
  }
}
