#include "./../include/transition.hpp"

Transition::Transition(int id_, std::string startState_, std::string outBand_, 
    std::string outStack_, std::string endState_, 
    std::vector<std::string> stackGains_): id(id_), startState(startState_),
    outBand(outBand_), outStack(outStack_), endState(endState_),
    stackGains(stackGains_) 
{}
    
Transition::Transition() 
{}

std::string Transition::getStartState() 
{
  return startState;
}

std::string Transition::getOutBand() 
{
  return outBand;
}

std::string Transition::getOutStack() 
{
  return outStack;
}

std::string Transition::getEndState() 
{
  return endState;
}

std::vector<std::string> Transition::getStackGains() 
{
  return stackGains;
}

int Transition::getId() 
{
  return id;
}

void Transition::log() 
{
  std::cout << id << ": (" << startState << ", " << outBand << ", ";
  std::cout << outStack << ", " << endState << ", ";
  for (int i = 0; i < stackGains.size(); i++) {
    std::cout << "[" << stackGains[i] << "]";
  }
  std::cout << ")" << std::endl;
}
