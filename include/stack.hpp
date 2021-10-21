#ifndef __STACK_H__
#define __STACK_H__

#include <iostream>
#include <vector>
#include <string>
#include <stack>

class Stack {
  private:
    std::stack<std::string> content;
    std::vector<std::string> alphabet;

  public:
    Stack();
    void push(std::string symbol);
    void pop();
    std::string top();
    void setAlphabet(std::vector<std::string> newAlphabet);
    void addToAlphabet(std::string symbol);
    void checkInAlphabet(std::string symbol);
    void logAlphabet();
    void logContent();
    void clear();
    bool empty();
};

#endif // __STACK_H__