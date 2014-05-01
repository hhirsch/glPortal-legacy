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
#include <wchar.h>
#include <locale.h> 
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
        characterConstraintsArray = SyntaxConstraintFactory::getCLikeCharacterMapArray();
      }

      void MapFileParser2::parse(std::ifstream &fileStream){
        if(Environment::DEBUG){
          //debug = true;
          debugCommands = true;
        }
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
                currentCharacter = std::string("whitespace");
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
        } else if(state == ParserState::READING_ARRAY){
          if(executeConstraint(characterConstraintsArray)){
          } else {
            stringStack += currentCharacter; 
          }
        } else {
          if((!executeConstraint(characterConstraints)) && (currentCharacter != "whitespace")){
            stringStack += currentCharacter; 
          }

        }
      }
    

      bool MapFileParser2::executeConstraint(std::map<std::string, std::vector<SyntaxConstraint> > &constraintMap){
        ParserState newState;
        if((constraintMap.find(currentCharacter) != constraintMap.end())){
          std::vector<SyntaxConstraint> constraintVector;
          
          if(currentCharacter != " "){
            constraintVector = constraintMap.at(currentCharacter);
          } 
          bool hasValidState = false;

          if(debug){
            cout << "\n";
            cout << "char found in map." << "\n";
            cout << "char: " << currentCharacter << "\n";
            cout << "before_state: " << parserStateStrings[(int)state] << "\n";
          }
          if(debug){
            cout << "state: " << parserStateStrings[(int)state] << "\n";
          }               


          for (int i=0; i<constraintVector.size(); i++) {
            SyntaxConstraint constraint = constraintVector[i];
            if(constraint.getIsValidPrerequisiteState(state)){
              hasValidState = true;
              if(debug){
                cout << "-> Detected valid state. \n";
              }
              std::vector<EventType> events = constraint.getEvents();
              for(std::vector<EventType>::iterator event = events.begin(); event != events.end(); ++event) {
                executeEvent(*event);
              }

              if(debug){
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
          if(stringStack != ""){
            command = stringStack;
          }
          break;
        case EventType::COPY_BUFFER_TO_PARAMETER:
          if((stringStack != "") && (stringStack != " ") && (!stringStack.empty() && (stringStack.size() > 0) && (stringStack[0] != '\0'))){
            if(debugCommands){
              //              cout << "Pushing "<< stringStack.size() << " par from stack:" << (int)stringStack.c_str()[0] << flush;
              cout << "Pushing "<< stringStack.size() << " par from stack:" << flush;
              printf("0x%x\n",(int)stringStack.c_str()[0]);
            }
            parameters.push_back(stringStack);
          }
          break;
        case EventType::CLEAR_BUFFER:
          clearStringStack();
          break;
        case EventType::EXECUTE:
          if(debugCommands){
            cout << "command found: " << command << "\n";
            if(false){
              for (unsigned n=0; n<parameters.size(); ++n) {
                cout << parameters.at( n ) << "\n ";
              }
            }
          }
          executeCurrentCommand();
          break;
        }
      }

      void MapFileParser2::executeCurrentCommand(){
        if(command == "addLight"){
          Light light(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          this->gameMap.addLight(light);
        }

        if(command == "setSpawn"){
          if(parameters.size() == 3){
            this->gameMap.setSpawnPosition(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          } else {
            cout << WRONG_PARAMETER_COUNT_MESSAGE << "\n";
          }
        }

        if(command == "addCake"){
          if(parameters.size() == 3){
            this->gameMap.setEndPosition(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          } else {
            cout << WRONG_PARAMETER_COUNT_MESSAGE << "\n";
          }
        }

        if(command == "addBoxes"){
          float values[parameters.size()];
          if((parameters.size()-1) % 6 == 0){
            for(int i = 1; i <= parameters.size()-1; i++){
              values[i-1] = ::atof(parameters.at(i).c_str());
              cout << parameters.at(i) << "#*";
            }

            this->gameMap.addWallBox(Box(values, TID_WALL));
            
          } else {
            cout << WRONG_PARAMETER_COUNT_MESSAGE << " COUNT: " << parameters.size() <<  "\n";
            for(int i = 0; i <= parameters.size()-1; i++){
              cout << parameters.at(i) << "?!";
            }
          }
        }
        parameters.clear();
        command = "";
      }

      void MapFileParser2::clearStringStack(){
        stringStack = "";      
      }

      void MapFileParser2::throwException(){
        if(sizeof(parserStateStrings) >= (int)state){
          std::string message = "Got \"" + currentCharacter + "\" while state was " + parserStateStrings[(int)state] + ". "  + currentPositionMessage;
          throw Exception(message);
        } else {

          stringstream stringStream;
          stringStream << (int)state;

          std::string message = STATE_TRANSLATION_MISSING_MESSAGE + " STATE: " + stringStream.str();
          throw Exception(message);
        }

      }
    }
  }
}
