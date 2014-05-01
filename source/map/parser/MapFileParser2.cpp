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
        } else if(state == ParserState::READING_ARRAY){
          executeConstraint(characterConstraintsArray);
        } else {
          if((!executeConstraint(characterConstraints)) && (currentCharacter != " ")){
            stringStack += currentCharacter; 
          }

        }
      }
    

      bool MapFileParser2::executeConstraint(std::map<std::string, std::vector<SyntaxConstraint> > &constraintMap){
        ParserState newState;
        if((constraintMap.find(currentCharacter) != constraintMap.end())){
          std::vector<SyntaxConstraint> constraintVector;

          if(currentCharacter == " "){                     
            constraintVector = constraintMap.at("whitespace");
          } else {
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
          parameters.push_back(stringStack);
          break;
        case EventType::CLEAR_BUFFER:
          clearStringStack();
          break;
        case EventType::EXECUTE:
          executeCurrentCommand();
          if(debugCommands){
            cout << "command found: " << command << "\n";
                for (unsigned n=0; n<parameters.size(); ++n) {
                  cout << parameters.at( n ) << "\n ";
                }
          }
          break;
        }
      }

      void MapFileParser2::executeCurrentCommand(){
        if(command == "setLight"){
          Light light(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          this->gameMap.addLight(light);
        }

        if(command == "setSpawn"){
          if(parameters.size() == 3){
            this->gameMap.setSpawnPosition(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          } else {
            cout << "Got wrong ammount of parameters -> FAILURE\n";
          }
          //          
        }

        if(command == "addCake"){
          if(parameters.size() == 3){
            this->gameMap.setEndPosition(::atof(parameters.at(0).c_str()), ::atof(parameters.at(1).c_str()), ::atof(parameters.at(2).c_str()));
          } else {
            cout << "Got wrong ammount of parameters -> FAILURE\n";
          }
        }

        if(command == "addBoxes"){
          cout << parameters.size();
          float values[6];
          values[0] = ::atof(parameters.at(1).c_str());
          cout << parameters.at(1);
          //          values[1] = ::atof(parameters.at(2).c_str());
          /*values[2] = ::atof(parameters.at(3).c_str());
          values[3] = ::atof(parameters.at(4).c_str());
          values[4] = ::atof(parameters.at(5).c_str());
          values[5] = ::atof(parameters.at(6).c_str());*/
          //          this->gameMap.addWallBox(Box(values, TID_WALL));
          //          void set(float x1, float y1, float z1, float x2, float y2, float z2, TEXTURE_ID type = TID_NONE)          
        }

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
