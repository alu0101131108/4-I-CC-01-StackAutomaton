#include "./../include/automaton.hpp"
Automaton::Automaton() 
{
  graphHead = NULL;
  generatedCount = 0;
  stepMode = false;
}

void Automaton::loadFromFile(std::string filename) 
{
  // Open file and store in a vector, discarding comments.
  std::ifstream ifs("./../input-files/" + filename);
  if (!ifs.is_open()) {
    std::cout << "Error - Can't open input file: " + filename << std::endl;
    exit(-1);
  }
  std::vector<std::string> text;
  std::string line;
  while (std::getline(ifs, line)) {
    if (line.size() > 0 && line[0] != '#')
      text.push_back(line);
  }
  ifs.close();

  // State set.
  states.clear();
  std::string symbol;
  std::stringstream iss(text[0]);
  while (!iss.eof()) {
    iss >> symbol;
    states.push_back(symbol);
  }

  // Band alphabet.
  inputBand = Band();
  iss.clear();
  iss.str(text[1]);
  while (!iss.eof()) {
    iss >> symbol;
    inputBand.addToAlphabet(symbol);
  }

  // Stack alphabet.
  stack = Stack();
  iss.clear();
  iss.str(text[2]);
  while (!iss.eof()) {
    iss >> symbol;
    stack.addToAlphabet(symbol);
  }

  // Initial state.
  iss.clear();
  iss.str(text[3]);
  iss >> symbol;
  checkStateInSet(symbol);
  initialState = symbol;
  state = "";

  // Initial Stack Symbol.
  iss.clear();
  iss.str(text[4]);
  iss >> symbol;
  stack.checkInAlphabet(symbol);
  initialStackSymbol = symbol;

  // Transitions.
  transitions.clear();
  int id;
  std::string startState, outBand, outStack, endState;
  std::vector<std::string> stackGains;
  for (int i = 5; i < text.size(); i++) {
    id = i - 4;
    iss.clear();
    iss.str(text[i]);
    iss >> startState;
    iss >> outBand;
    iss >> outStack;
    iss >> endState;

    stackGains.clear();
    while(!iss.eof()) {
      iss >> symbol;
      stackGains.push_back(symbol);
    }
    addTransition(Transition(id, startState, outBand, outStack, endState, stackGains));
  }

  // Restart rest attributes.
  graphHead = NULL;
  generatedCount = 0;
  stepMode = false;
}

void Automaton::logInfo() 
{
  std::cout << "INFORMATION" << std::endl;

  std::cout << "States set: {";
  for (int i = 0; i < states.size(); i++) {
    std::cout << "[" << states[i] << "]";
  }
  std::cout << "}" << std::endl;
  std::cout << "Initial State: " << initialState << std::endl;
  std::cout << "Current State: " << state << std::endl;

  inputBand.logAlphabet();
  inputBand.logContent();

  stack.logAlphabet();
  std::cout << "Initial Stack Symbol: " << initialStackSymbol << std::endl;
  stack.logContent();

  std::cout << "Transitions:" << std::endl;
  for (int i = 0; i < transitions.size(); i++) {
    transitions[i].log();
  }
  std::cout << std::endl;
}

void Automaton::checkStateInSet(std::string state_) 
{
  bool belongs = false;
  for (int i = 0; i < states.size(); i++) {
    if (state_ == states[i])
      belongs = true;
  }
  if (!belongs) {
    std::cout << "Error - State not in automaton's set: " << state_ << std::endl;
    exit(-1);
  }
}

void Automaton::setState(std::string newState) 
{
  checkStateInSet(newState);
  state = newState;
}

void Automaton::setStepMode(bool mode) 
{
  stepMode = mode;
}

void Automaton::addTransition(Transition newTransition) 
{
  checkStateInSet(newTransition.getStartState());
  inputBand.checkInAlphabet(newTransition.getOutBand());
  stack.checkInAlphabet(newTransition.getOutStack());
  checkStateInSet(newTransition.getEndState());
  std::vector<std::string> stackGains = newTransition.getStackGains();
  for (int i = 0; i < stackGains.size(); i++) {
    stack.checkInAlphabet(stackGains[i]);
  }
  transitions.push_back(newTransition);
}



bool Automaton::isTransitionFactible(Transition transition) 
{
  return (state == transition.getStartState() &&
      (transition.getOutBand() == "." || (!inputBand.empty() && inputBand.getHead() == transition.getOutBand())) &&
      (!stack.empty() && stack.top() == transition.getOutStack()));
}

bool Automaton::validateString(std::string string) 
{
  // Reset automaton values and fill input data.
  inputBand.clear();
  for (int i = 0; i < string.size(); i++) {
    inputBand.addToContent(std::string(1, string[i]));
  }
  stack.clear();
  stack.push(initialStackSymbol);
  setState(initialState);
  generatedCount = 0;

  // Create graph head and start recursive explore.
  graphHead = new Node();
  return exploreNode(graphHead);
}

// Apply its transition and capture values, then explore childs.
bool Automaton::exploreNode(Node* target) 
{
  bool accepted = false;

  // Apply transition (unless its the graph head node) and capture values.
  if (target -> getId() != "*") applyTransition(target -> getTransition());
  target -> setVisited(true);
  captureValuesInNode(target);

  // Generate childs with their associated transition.
  generateChilds(target);

  // Verify acceptance condition.
  if (validConditionAccomplished()) {
    accepted = true;
    target -> setExploreTurn(target -> getExploreTurn() * -1); // Mark as validation node.
  }

  // Step by step mode.
  if(stepMode) {
    target -> log();
    if (accepted)
      std::cout << "VALID CONDITION ACCOMPLISHED" << std::endl << std::endl;
  }

  // Explore each child.
  std::vector<Node*> childs = target -> getChilds();
  for (int i = 0; i < childs.size() && accepted == false; i++) {
    if (i != 0) returnValuesFromNode(target);
    accepted = exploreNode(childs[i]);
  }
  
  // Graphviz code.
  generateGraphvizCode();

  return accepted;
}

void Automaton::applyTransition(Transition instruction) 
{
  setState(instruction.getEndState());
  instruction.getOutBand() == "." ? inputBand.consume(0) : inputBand.consume(1);
  stack.pop();
  std::vector<std::string> stackGains = instruction.getStackGains();
  for (int i = stackGains.size() - 1; i >= 0; i--) {
    if (stackGains[i] != ".")
      stack.push(stackGains[i]);
  }
}

void Automaton::captureValuesInNode(Node* target) 
{
  target -> setBand(inputBand);
  target -> setStack(stack);
  target -> setState(state);
}

void Automaton::returnValuesFromNode(Node* target) 
{
  inputBand = target -> getBand();
  stack = target -> getStack();
  state = target -> getState();
  if (stepMode) {
    std::cout << "Branch discarded, restore from node: ";
    std::cout << target -> getExploreTurn() << std::endl << std::endl;
  }
}

void Automaton::generateChilds(Node* target) 
{
  for (int i = 0; i < transitions.size(); i++) {
    if (isTransitionFactible(transitions[i])) {
      Node* child = new Node();
      child -> setTransition(transitions[i]);
      child -> setExploreTurn(++generatedCount);
      target -> addChild(child);
    }
  }
}

bool Automaton::validConditionAccomplished() 
{
  return (inputBand.empty() && stack.empty());
}

void Automaton::generateGraphvizCode() 
{
  graphHead -> generateGraphvizCode();
}

