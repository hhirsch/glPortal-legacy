#ifndef __EXCEPTION_HPP
#define __EXCEPTION_HPP
#include <cstdio>
#include <string>
using namespace std;

class Exception {
public:
  const char* message;
  Exception(const char* message);
  void print();
  const char* getMessage();
};
#endif
