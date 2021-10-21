#include "./../include/stack.hpp"

Stack::Stack() 
{}

void Stack::push(std::string symbol) 
{
  checkInAlphabet(symbol);
  content.push(symbol);
}

void Stack::pop() 
{
  if (empty()) {
    std::cout << "Error - pop(): Stack is empty." << std::endl;
    exit(-1);
  } 
  else
    content.pop();
}

std::string Stack::top() 
{
  if (empty()) {
    std::cout << "Error - top(): Stack is empty." << std::endl;
    exit(-1);
  }
  return content.top();
}

void Stack::setAlphabet(std::vector<std::string> newAlphabet) 
{
  alphabet = newAlphabet;
}

void Stack::addToAlphabet(std::string symbol) 
{
  alphabet.push_back(symbol);
}

void Stack::checkInAlphabet(std::string symbol) 
{
  if (symbol == ".") return;
  bool belongs = false;
  for (int i = 0; i < alphabet.size(); i++) {
    if (symbol == alphabet[i])
      belongs = true;
  }
  if (!belongs) {
    std::cout << "Error - Symbol not in stack's alphabet: " << symbol << std::endl;
    exit(-1);
  }
}

void Stack::logAlphabet() 
{
  std::cout << "Stack Alphabet: {";
  for (int i = 0; i < alphabet.size(); i++) {
    std::cout << "[" << alphabet[i] << "]";
  }
  std::cout << "}" << std::endl;
}

void Stack::logContent() 
{
  std::stack<std::string> contentCopy = content;

  std::cout << "Stack Content: ";
  while (!contentCopy.empty()) {
    std::cout << "[" << contentCopy.top() << "]";
    contentCopy.pop();
  }
  std::cout << std::endl;
}

void Stack::clear() 
{
  while(!content.empty()) content.pop();
  // alphabet.clear();
}

bool Stack::empty() 
{
  return content.empty();
}
