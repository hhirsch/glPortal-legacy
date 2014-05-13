#include "Parser.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>      
#include "Lexer.hpp"
#include "LexerEvent.hpp"
#include "Scanner.hpp"
#include "StateMachine.hpp"

namespace glPortal {
  namespace util{
    namespace parser{
      Parser::Parser(std::string filename):  rootNode(TreeNodeType::ROOT, ""), lineNumber(0), lexer(){
	this->scanner = new Scanner(this);
        this->filename = filename;
        this->fileStream = new std::ifstream(filename, std::ifstream::in);

        if(!fileStream){
          throw std::invalid_argument("File " + filename + " not found.");
        }
      
      }

      void Parser::parse(std::ifstream &fileStream){
        std::string line, string;
        while(std::getline(fileStream, line)){
          lineNumber++;
          //std::istringstream iss(line);

          if(line.length() > 0) {
            try{
	      //              this->lexer->analyze();
	      //this->scanner.scan(line);
            } catch(const std::logic_error& e){
            }
          }
        }        
      }

      void Parser::addNode(LexerEvent event, std::string data){
	if(event == LexerEvent::COMMAND){
	  currentNode = new TreeNode(TreeNodeType::ROOT, std::string(""));
	}
      }

      void Parser::generateTree(){
        while(fileStream->good()) {
          //state = ParserState::READING_COMMAND;
          //          this->parse(fileStream);
          fileStream->close();
        }
      }

      TreeNode* Parser::getRootNode(){
        return &rootNode;
      }
    }
  }
}
