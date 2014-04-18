#include "Exception.hpp"

Exception::Exception(std::string message){
  this->message = message; 
}

void Exception::print() {
  //printf(this->message);
}

std::string Exception::getMessage() {
  return this->message;
}
