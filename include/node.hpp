#ifndef __NODE_H__
#define __NODE_H__

#include "./band.hpp"
#include "./stack.hpp"
#include "./transition.hpp"
#include <vector>
#include <string>
#include <fstream>

class Node {
  private:
    Transition transition;
    std::string state;
    Band inputBand;
    Stack stack;
    std::vector<Node*> childs;
    bool visited;
    std::string id;
    int exploreTurn;

  public:
    Node();

    Transition getTransition();
    std::string getState();
    Band getBand();
    Stack getStack();
    std::vector<Node*> getChilds();
    bool getVisited();
    std::string getId();
    int getExploreTurn();

    void setTransition(Transition newTransition);
    void setState(std::string newState);
    void setBand(Band newBand);
    void setStack(Stack newStack);
    void setVisited(bool newVisited);
    void setId(std::string newId);
    void setExploreTurn(int value);
    
    void addChild(Node* newChild);
    void log();
    void generateGraphvizCode();
    std::string getVisitedIdString();
    std::string getTransitionsString();
};

#endif // __NODE_H__