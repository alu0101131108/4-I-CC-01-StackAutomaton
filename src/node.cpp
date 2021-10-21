#include "./../include/node.hpp"

Node::Node()
{
  id = "*";
  visited = false;
}

Transition Node::getTransition() 
{
  return transition; 
}

std::string Node::getState() 
{
  return state;
}

Band Node::getBand() 
{
  return inputBand;
}

Stack Node::getStack() 
{
  return stack;
}

std::vector<Node*> Node::getChilds() 
{
  return childs;
}

bool Node::getVisited() 
{
  return visited;
}

std::string Node::getId() 
{
  return id;
}

int Node::getExploreTurn() 
{
  return exploreTurn;
}

void Node::setTransition(Transition newTransition) 
{
  transition = newTransition;
  id = std::to_string(transition.getId());
}

void Node::setState(std::string newState) 
{
  state = newState;
}

void Node::setBand(Band newBand) 
{
  inputBand = newBand;
}

void Node::setStack(Stack newStack) 
{
  stack = newStack;
}

void Node::setVisited(bool newVisited) 
{
  visited = newVisited;
}

void Node::setId(std::string newId) 
{
  id = newId;
}

void Node::setExploreTurn(int value) 
{
  exploreTurn = value;
}

void Node::addChild(Node* newChild) 
{
  childs.push_back(newChild);
}

void Node::log() 
{
  std::cout << "Node id: " << exploreTurn << std::endl;
  std::cout << "Transition: " << id << std::endl;
  std::cout << "State: " << state << std::endl;
  inputBand.logContent();
  stack.logContent();
  std::cout << "Childs: ";
  for (int i = 0; i < childs.size(); i++) {
    std::cout << "[" << childs[i] -> getId() << "]";
  }
  std::cout << std::endl << std::endl;
}

void Node::generateGraphvizCode() 
{
  std::string visitedIds = getVisitedIdString();
  std::string transitions = getTransitionsString();

  std::ofstream ofs;
  ofs.open("./../graphviz-code.txt");
  ofs << "digraph TransitionGraph {\n  rankdir = TB;\n";
  ofs << "  node [shape = none]; \"*\";\n";
  ofs << "  node [shape = doublecircle]; " + visitedIds + ";\n";
  ofs << "  node [shape = circle];\n";
  ofs << transitions + "}";
  ofs.close();
}

std::string Node::getVisitedIdString() 
{
  std::string result = "";
  std::string exploreTurnString = id == "*" ? "*" : std::to_string(exploreTurn);

  if (visited) {
    result += " \"" + exploreTurnString + "\"";
  }
  
  for (int i = 0; i < childs.size(); i++) {
    result += childs[i] -> getVisitedIdString();
  }

  return result;
}

std::string Node::getTransitionsString() 
{
  std::string result = "";
  std::string exploreTurnString = id == "*" ? "*" : std::to_string(exploreTurn);

  for (int i = 0; i < childs.size(); i++) {
    result += "\"" + exploreTurnString + "\" -> \"" + std::to_string(childs[i] -> getExploreTurn()) + "\"";
    result += " [label=\"" + childs[i] -> getId() + "\"];\n";
  }
  
  for (int i = 0; i < childs.size(); i++) {
    result += childs[i] -> getTransitionsString();
  }

  return result;
}