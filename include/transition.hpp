#ifndef __TRANSITION_H__
#define __TRANSITION_H__

#include <iostream>
#include <vector>
#include <string>

class Transition {
  private:
    int id;
    std::string startState;
    std::string outBand;
    std::string outStack;
    std::string endState;
    std::vector<std::string> stackGains;

  public:
    Transition();
    Transition(int id, std::string startState_, std::string outBand_, 
        std::string outStack_, std::string endState_, 
        std::vector<std::string> stackGains_);
    std::string getStartState();
    std::string getOutBand();
    std::string getOutStack();
    std::string getEndState();
    std::vector<std::string> getStackGains();
    int getId();
    void log();

};

#endif // __TRANSITION_H__