#ifndef __EXCEPTION_HPP
#define __EXCEPTION_HPP
#include <stdio.h>
#include <string>
using namespace std;

class Exception {
public:
  std::string message;
  Exception(std::string message);
  void print();
  std::string getMessage();
};
#endif
