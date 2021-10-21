#ifndef __AUTOMATON_H__
#define __AUTOMATON_H__

#include "./band.hpp"
#include "./stack.hpp"
#include "./transition.hpp"
#include "./node.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


class Automaton {
  private:
    Band inputBand;
    Stack stack;
    std::string state;
    std::vector<Transition> transitions;
    std::vector<std::string> states;
    std::string initialState;
    std::string initialStackSymbol;
    Node* graphHead;
    int generatedCount;
    bool stepMode;

  public:
    Automaton();
    void loadFromFile(std::string filename);
    void logInfo();
    void checkStateInSet(std::string state_);
    void setState(std::string newState);
    void setStepMode(bool mode);
    void addTransition(Transition newTransition);

    bool validateString(std::string string);
    bool exploreNode(Node* target);
    bool isTransitionFactible(Transition transition);
    void applyTransition(Transition instruction);
    void captureValuesInNode(Node* target);
    void returnValuesFromNode(Node* target);
    void generateChilds(Node* target);
    bool validConditionAccomplished();
    void generateGraphvizCode();
};
#endif // __AUTOMATON_H__