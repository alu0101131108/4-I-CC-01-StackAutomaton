#include "./../include/band.hpp"
Band::Band() 
{
  headIndex = 0;
}

void Band::setAlphabet(std::vector<std::string> newAlphabet) 
{
  alphabet = newAlphabet;
}

void Band::addToAlphabet(std::string symbol) 
{
  alphabet.push_back(symbol);
}

void Band::setContent(std::vector<std::string> newContent) 
{
  content = newContent;
}

void Band::addToContent(std::string symbol) 
{
  content.push_back(symbol);
}

void Band::consume(int steps = 0) 
{
  headIndex = headIndex + steps;
}

void Band::checkInAlphabet(std::string symbol) 
{
  if (symbol == ".") return;
  bool belongs = false;
  for (int i = 0; i < alphabet.size(); i++) {
    if (symbol == alphabet[i])
      belongs = true;
  }
  if (!belongs) {
    std::cout << "Error - Symbol not in band's alphabet: " << symbol << std::endl;
    exit(-1);
  }
}

std::string Band::getHead() 
{
  if (content.size() <= headIndex) {
    std::cout << "Error - Band headIndex out of range" << std::endl;
    exit(-1);
  }

  return content[headIndex];
}

void Band::logAlphabet() 
{
  std::cout << "Band Alphabet: {";
  for (int i = 0; i < alphabet.size(); i++) {
    std::cout << "[" << alphabet[i] << "]";
  }
  std::cout << "}" << std::endl;
}

void Band::logContent() 
{
  std::cout << "Band Content: ";
  for (int i = 0; i < content.size(); i++) {
    if (i == headIndex) 
      std::cout << "<[" << content[i] << "]>";
    else
      std::cout << "[" << content[i] << "]";
  }
  if (headIndex >= content.size())
    std::cout << "<>";
  std::cout << std::endl;
}

void Band::clear() 
{
  headIndex = 0;
  content.clear();
  // alphabet.clear();
}

bool Band::empty() 
{
  return headIndex >= content.size();
}
