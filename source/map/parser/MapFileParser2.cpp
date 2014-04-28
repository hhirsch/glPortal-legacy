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
#include "../../engine/Environment.hpp"
#include "../../Exception.hpp"
#include "../../util/Vector3f.hpp"
#include "EventType.hpp"
#include "ParserState.hpp"
#include "SyntaxConstraintFactory.hpp"
#include "SyntaxConstraint.hpp"

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
        characterConstraints = SyntaxConstraintFactory::getCLikeCharacterMap();
        characterConstraintsComments = SyntaxConstraintFactory::getCLikeCharacterMapComment();
      }

      void MapFileParser2::parse(std::ifstream &fileStream){
        std::string line, string;
        while(std::getline(fileStream, line)){
          if(state == ParserState::COMMENT){
            state = ParserState::READING_COMMAND;
          }
          lineNumber++;
          currentPositionMessage = "On line " + std::to_string(lineNumber) + " in file " + this->fileName + ".";
          std::istringstream iss(line);

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
        if((state == ParserState::COMMENT) ||
           (state == ParserState::WAITING_COMMENT) ||
           (state == ParserState::LONG_COMMENT) ||
           (state == ParserState::LONG_COMMENT_WAITING_TERMINATION)
           ){
          executeConstraint(characterConstraintsComments);
        } else {
          if((!executeConstraint(characterConstraints)) && (currentCharacter != " ")){
            stringStack += currentCharacter; 
          }

        }
      }
    

      bool MapFileParser2::executeConstraint(std::map<std::string, std::vector<SyntaxConstraint> > &constraintMap){
        ParserState newState;
        if((constraintMap.find(currentCharacter) != constraintMap.end())){
          cout << "\n";
          std::vector<SyntaxConstraint> constraintVector = constraintMap.at(currentCharacter);
          bool hasValidState = false;
          if(Environment::DEBUG){
            cout << "char found in map." << "\n";
            cout << "char: " << currentCharacter << "\n";
            cout << "before_state: " << parserStateStrings[(int)state] << "\n";
          }
          if(Environment::DEBUG){
            cout << "state: " << parserStateStrings[(int)state] << "\n";
          }

          for (int i=0; i<constraintVector.size(); i++) {
            SyntaxConstraint constraint = constraintVector[i];
            if(constraint.getIsValidPrerequisiteState(state)){
              hasValidState = true;
              if(Environment::DEBUG){
                cout << "-> Detected valid state. \n";
              }
              std::vector<EventType> events = constraint.getEvents();
              
              for(std::vector<EventType>::iterator event = events.begin(); event != events.end(); ++event) {
                executeEvent(*event);
              }
              if(Environment::DEBUG){
                cout << "switching: " << parserStateStrings[(int)state] << " to ";
                cout << parserStateStrings[(int)constraint.getResultState()] << "\n";
              }
              newState = constraint.getResultState();
            }
          } 
          
          if(newState == ParserState::PREVIOUS_STATE){
          } else {
            state = newState;
          }
          
          if((!hasValidState)){
            throwException();
          }

          return true;
        } else {
          // If there is no termination of the long comment, the comment is going on
          if(state == ParserState::LONG_COMMENT_WAITING_TERMINATION){
            state = ParserState::LONG_COMMENT;
          }
          return false;
        }
      }
  
      void MapFileParser2::executeEvent(EventType event){
        switch(event){
        case EventType::COPY_BUFFER_TO_COMMAND:
          //                                cout << "copy";
          command = stringStack;
          break;
        case EventType::CLEAR_BUFFER:
          //                                cout << "clear";
          clearStringStack();
          break;
        case EventType::EXECUTE:
          if(Environment::DEBUG){
            cout << "command found: " << command << "\n";
          }
          break;
        default:
          //                cout << "default\n";
          //                cout << (int)events[i] << "xxx";
          //                cout << (int)*event;
          break;
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

      void MapFileParser2::throwException(){
        std::string message = "Got \"" + currentCharacter + "\" while state was " + parserStateStrings[(int)state] + ". "  + currentPositionMessage;
        throw Exception(message);
      }
    }
  }
}
