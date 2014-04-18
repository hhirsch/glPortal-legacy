#include "MapFileParser2.hpp"
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include "../GameMap.hpp"
#include "../engine/Resources.hpp"
#include "../engine/StringConverter.hpp"
#include "../Exception.hpp"
#include "../util/Vector3f.hpp"

namespace glPortal {
  namespace map{

    /**
     * Get a map from a map file.
     *
     * @param filename Path to the map file
     */
    GameMap MapFileParser2::getMapFromFile(std::string filename) {
      this->fileName = filename;
      std::ifstream fileStream(filename, std::ifstream::in);

      this->gameMap.flush();

      if(!fileStream){
        cout << NO_FILE_MESSAGE;
        this->gameMap.setIsLastScreen();
        return this->gameMap;
      }
      
      while(fileStream.good()) {
        state = PARSER_READING_COMMAND;
        this->parse(fileStream);
        fileStream.close();
        return this->gameMap;
      }
    }

    void MapFileParser2::parse(std::ifstream &fileStream){
      std::string line, string;
      while(std::getline(fileStream, line)){
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
      if(currentCharacter == " "){
      } else if(currentCharacter == "/"){
        if(state == PARSER_READING_COMMAND){
          state = PARSER_LONG_COMMENT;
        } else if(state == PARSER_LONG_COMMENT){
          state = PARSER_READING_COMMAND;
        } else {
          throwException();
        }
      } else if(state == PARSER_LONG_COMMENT){
      } else if(characterStateMatch("(", PARSER_READING_COMMAND)){
        state = PARSER_READING_PARAMETERS;
        command = stringStack;
        clearStringStack();
      } else if(characterStateMatch(",", PARSER_READING_PARAMETERS)){
        parameters.push_back(stringStack);
        clearStringStack();
      } else if(characterStateMatch(")", PARSER_READING_PARAMETERS)){
        state = PARSER_WAITING_TERMINATION;
        parameters.push_back(stringStack);
        clearStringStack();
      } else if(currentCharacter == ";"){
        if(state == PARSER_WAITING_TERMINATION){
          state = PARSER_READING_COMMAND;
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

    }

    void MapFileParser2::executeCurrentCommand(){
      if(command == "setSpawn"){
        cout << "Setting spawn";
      }
    }

    void MapFileParser2::clearStringStack(){
      stringStack = "";      
    }

    bool MapFileParser2::characterStateMatch(std::string character, PARSER_STATE stateToCheck){
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
      std::string message = "Got \"" + currentCharacter + "\" while state was " + parserStateStrings[state] + ". "  + currentPositionMessage;
      throw Exception(message);
    }
  }
}
