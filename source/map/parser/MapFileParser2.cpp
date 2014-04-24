#include "MapFileParser2.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../../GameMap.hpp"
#include "../../engine/Resources.hpp"
#include "../../engine/StringConverter.hpp"
#include "../../Exception.hpp"
#include "../../util/Vector3f.hpp"
#include "EventType.hpp"
#include "ParserState.hpp"

namespace glPortal {
  namespace map{
    namespace parser{
    /**
     * Get a map from a map file.
     *
     * @param filename Path to the map file
     */
    GameMap MapFileParser2::getMapFromFile(std::string filename) {
      initializeSyntax();
      this->fileName = filename;
      std::ifstream fileStream(filename, std::ifstream::in);

      this->gameMap.flush();

      if(!fileStream){
        cout << NO_FILE_MESSAGE;
        this->gameMap.setIsLastScreen();
        return this->gameMap;
      }
      
      while(fileStream.good()) {
        state = ParserState::READING_COMMAND;
        this->parse(fileStream);
        fileStream.close();
        return this->gameMap;
      }
    }
      
    void MapFileParser2::initializeSyntax(){
      SyntaxConstraint brace, closingBrace, comma, 
        semicolon, curlyBrace, closingCurlyBrace,
        commentInit, comment, longComment;
      brace.addPrerequisiteState(ParserState::READING_COMMAND);
      brace.setResultState(ParserState::READING_PARAMETERS);
      brace.addEvent(EventType::COPY_BUFFER_TO_COMMAND);
      brace.addEvent(EventType::CLEAR_BUFFER);
      vector<SyntaxConstraint> braceVector;
      braceVector.push_back(brace);
      characterConstraints["("] = braceVector;

      closingBrace.addPrerequisiteState(ParserState::READING_PARAMETERS);
      closingBrace.setResultState(ParserState::WAITING_TERMINATION);
      closingBrace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
      closingBrace.addEvent(EventType::CLEAR_BUFFER);
      vector<SyntaxConstraint> closingBraceVector;
      closingBraceVector.push_back(closingBrace);
      characterConstraints[")"] = closingBraceVector;

      comma.addPrerequisiteState(ParserState::READING_PARAMETERS);
      comma.addPrerequisiteState(ParserState::READING_ARRAY);
      comma.setResultState(ParserState::PREVIOUS_STATE);
      comma.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
      comma.addEvent(EventType::CLEAR_BUFFER);
      vector<SyntaxConstraint> commaVector;
      commaVector.push_back(comma);
      characterConstraints[","] = commaVector;

      semicolon.addPrerequisiteState(ParserState::WAITING_TERMINATION);
      semicolon.setResultState(ParserState::READING_COMMAND);
      semicolon.addEvent(EventType::CLEAR_BUFFER);
      semicolon.addEvent(EventType::EXECUTE);
      vector<SyntaxConstraint> semicolonVector;
      semicolonVector.push_back(semicolon);
      characterConstraints[";"] = semicolonVector;

      curlyBrace.addPrerequisiteState(ParserState::WAITING_TERMINATION);
      curlyBrace.setResultState(ParserState::READING_ARRAY);
      vector<SyntaxConstraint> curlyBraceVector;
      curlyBraceVector.push_back(curlyBrace);
      characterConstraints["{"] = curlyBraceVector;

      closingCurlyBrace.addPrerequisiteState(ParserState::READING_ARRAY);
      closingCurlyBrace.setResultState(ParserState::READING_COMMAND);
      closingCurlyBrace.addEvent(EventType::COPY_BUFFER_TO_PARAMETER);
      closingCurlyBrace.addEvent(EventType::CLEAR_BUFFER);
      closingCurlyBrace.addEvent(EventType::EXECUTE);
      vector<SyntaxConstraint> closingCurlyBraceVector;
      curlyBraceVector.push_back(closingCurlyBrace);
      characterConstraints["}"] = closingCurlyBraceVector;
      /*
      commentInit.addPrerequisiteState(ParserState::READING_COMMAND);
      commentInit.setResultState(ParserState::WAITING_COMMENT);
      vector<SyntaxConstraint> commentInitVector;
      commentInitVector.push_back(commentInit);
      characterConstraints["/"] = commentInitVector; */
      /*
      commentInit.addPrerequisiteState(ParserState::WAITING_COMMENT);
      commentInit.setResultState(ParserState::LONG_COMMENT);
      vector<SyntaxConstraint> commentInitVector;
      characterConstraints["*"] = commentInit;*/
    }

    void MapFileParser2::parse(std::ifstream &fileStream){
      std::string line, string;
      while(std::getline(fileStream, line)){
        lineNumber++;
        currentPositionMessage = "On line " + std::to_string(lineNumber) + " in file " + this->fileName + ".";
        std::istringstream iss(line);
        if(skipLine){
          skipLine = false;
        }

        if(revertStatus){
          revertStatus = false;
          state = ParserState::READING_COMMAND;
        }

        if(line.length() > 0) {
          for(int i = 0; i <= line.length(); i++){
            stringstream conversionStream;
            conversionStream << line[i];
            if(line[i] == ' '){
              currentCharacter = std::string(" ");
            } else {
              conversionStream >> currentCharacter;
            }
            this->tokenize();
          }
        }
      }        
    }

    void MapFileParser2::tokenize(){
      std::string message;
      if(characterConstraints.find(currentCharacter) != characterConstraints.end()){
        std::vector<SyntaxConstraint> constraintVector = characterConstraints.at(currentCharacter);
        bool hasValidState = false;
        for (int i=0; i<constraintVector.size(); i++) {
          //          cout << (int)constraintVector[i].getResultState() << endl;
          //          SyntaxConstraint constraint = characterConstraints.at(i);
          SyntaxConstraint constraint = constraintVector[i];
          //          std::vector<ParserState> preStates = constraint.getPrerequisiteStates();
          if(constraint.getIsValidPrerequisiteState(state)){
            hasValidState = true;
            std::vector<EventType> events = constraint.getEvents();
            for(std::vector<EventType>::iterator event = events.begin(); event != events.end(); ++event) {
            //            cout << events.size() << " #";
            //for (int i=0; i<events.size(); i++) {
              //cout << (int)events[2];
              //  cout << "KJHGLKHJ";
              switch(*event){
                //   switch(events[i]){
              case EventType::COPY_BUFFER_TO_COMMAND:
                //                                cout << "copy";
                command = stringStack;
                break;
              case EventType::CLEAR_BUFFER:
                //                                cout << "clear";
                clearStringStack();
                break;
              case EventType::EXECUTE:
                cout << "exe";
                cout << command + "\n";
                break;
              default:
                //                cout << "default\n";
                //                cout << (int)events[i] << "xxx";
                //                cout << (int)*event;
                break;
              }
            }
          }         
        } 

        if(!hasValidState){
          throwException();
        }

        //cout << (int)constraintVector.at(0).getResultState();
        /* for(std::vector<SyntaxConstraint>::iterator constraint = constraintVector.begin(); constraint != constraintVector.end(); ++constraint) {
        //SyntaxConstraint constraint = characterConstraints.at(currentCharacter);
                 std::vector<ParserState> preStates = *constraint.getPrerequisiteStates();
          if(constraint.getIsValidPrerequisiteState(state)){
            std::vector<EventType> events = *constraint.getEvents();
            for(std::vector<EventType>::iterator event = events.begin(); event != events.end(); ++event) {
              switch(*event){
              case EventType::COPY_BUFFER_TO_COMMAND:
                command = stringStack;
                break;
              case EventType::CLEAR_BUFFER:
                clearStringStack();
                break;
              case EventType::EXECUTE:
                cout << command + "\n";
                break;
              default:
                
                break;
              }
            }
          }
        }
        if(constraint.getResultState() != ParserState::PREVIOUS_STATE){
          state = constraint.getResultState();
          } */
      } else {
      stringStack += currentCharacter; 
        //this->throwException();
      }

        //                  if(std::find(preStates.begin(), preStates.end(), state)!=preStates.end()){
        //          }
            /*
            std::vector<EventType> events = constraint.getEvents();
            for(std::vector<EventType>::iterator event = events.begin(); event != events.end(); ++event) {
              switch(*event){
              case EventType::COPY_BUFFER_TO_COMMAND:
                command = stringStack;
                break;
              case EventType::CLEAR_BUFFER:
                clearStringStack();
                break;
              default:
                
                break;
                 }
*/
              //              if(*event == EventType::COPY_BUFFER_TO_COMMAND){
              //  command = stringStack; 
              ///}



              //            }
          
      //     cout << command;
          //}
    
      /*
      extractParameters();
      detectComments();
      if((state == PARSER_COMMENT) || (state == PARSER_WAITING_COMMENT) || (state == PARSER_LONG_COMMENT) || (skipLine == true)){
      } else if(currentCharacter == " "){
      } else if(characterStateMatch("(", PARSER_READING_COMMAND)){
        state = PARSER_READING_PARAMETERS;
        command = stringStack;
        clearStringStack();
      } else if(characterStateMatch(")", PARSER_READING_PARAMETERS)){
        state = PARSER_WAITING_TERMINATION;
        parameters.push_back(stringStack);
        clearStringStack();
      } else if(currentCharacter == ";"){
        if(state == PARSER_WAITING_TERMINATION){
          state = PARSER_READING_COMMAND;
          executeCurrentCommand();
        } else {
          throwException();
        }
      } else if(currentCharacter == "{"){
        if(state == PARSER_WAITING_TERMINATION){
          state = PARSER_READING_ARRAY;
        } else {
          throwException();
        }
      } else if(characterStateMatch("}", PARSER_READING_ARRAY)){
        state = PARSER_READING_COMMAND;
        parameters.push_back(stringStack);
        clearStringStack();
        executeCurrentCommand();
      } else {
        stringStack += currentCharacter;
      }
      //                  cout << currentCharacter;
      //    cout << " => " << parserStateStrings[state] << "\n";
      */
    }

    void MapFileParser2::detectComments(){
      if(currentCharacter == "*"){
        if(state == ParserState::WAITING_COMMENT){
          state = ParserState::LONG_COMMENT;
          skipLine = true;
        }
      }
      if(currentCharacter == "/"){
        if(state == ParserState::READING_COMMAND){
          state = ParserState::WAITING_COMMENT;
        } else if(state == ParserState::WAITING_COMMENT){
          state = ParserState::COMMENT;
          skipLine = true;
          revertStatus = true;
        } else if(state == ParserState::LONG_COMMENT){
          state = ParserState::READING_COMMAND;
          skipLine = true;
        } else {
          throwException();
        }    
      }
    }

    void MapFileParser2::extractParameters(){
      if(currentCharacter == ","){
        if((state == ParserState::READING_ARRAY) || (state == ParserState::READING_PARAMETERS)){
          parameters.push_back(stringStack);
          clearStringStack();
        } else {
          throwException();
        }
      }
    }

    void MapFileParser2::executeCurrentCommand(){
      if(command == "setSpawn"){        
        cout << "par" << "\n";
        cout << command;
        cout << parameters.at(0);
        cout << parameters.at(1);
        cout << "\n";
      } else {
        cout << "par" << "\n";
        cout << command;
        cout << parameters.at(0);
        cout << parameters.at(1);
        cout << "\n";
      }
      cout << "clearing" << "\n";
      parameters.clear();
    }

    void MapFileParser2::clearStringStack(){
      stringStack = "";      
    }

    bool MapFileParser2::characterStateMatch(std::string character, ParserState stateToCheck){
      if(currentCharacter != character){
        return false;
      }
      if(state == stateToCheck){
        return true;
      } else {
        throwException();
      }
      return false;
    }

    void MapFileParser2::throwException(){
      std::string message = "Got \"" + currentCharacter + "\" while state was " + parserStateStrings[(int)state] + ". "  + currentPositionMessage;
      throw Exception(message);
    }
    }
  }
}
