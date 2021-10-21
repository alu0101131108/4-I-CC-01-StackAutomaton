#include "./../include/automaton.hpp"
#include <iostream>
#include <vector>
#include <string>

const char WALL = '='; 
const int WIDTH = 100;
const int INPUT_SEPARATION = 30;
std::vector<std::string> knownFiles = {"APv.txt", "APv-2.txt", "APv-3.txt"};

std::string index(int i) {
  return "(" + std::to_string(knownFiles.size() + i) + ") ";
}

std::string tabString(std::string str) {
  int offset = (WIDTH - str.size()) / 2;
  for (int i = 0; i <= offset; i++) {
    str = i != offset ? " " + str + " " : WALL + str + WALL;
  }
  if (str.size() % 2 == 0) str.pop_back();
  str.pop_back();
  str.pop_back();
  str.push_back(WALL);  
  return str;
}

int main(int argc, char **argv)
{
  int option, totalOptions = 3;
  Automaton APv;
  bool stepMode = false;
  std::string filename, input;

  std::system("clear");
  std::cout << std::string(WIDTH, WALL) << std::endl;
  std::cout << std::string((WIDTH - 25) / 2 + 1, WALL) + "STACK AUTOMATON SIMULATOR" + std::string((WIDTH - 25) / 2, WALL)<< std::endl;
  std::cout << std::string(WIDTH, WALL) << std::endl;
  std::cout << tabString("Choose an option:") << std::endl;
  for (int i = 0; i < knownFiles.size(); i++) {
    std::cout << tabString("(" + std::to_string(i + 1) + "): " + 
        "Load " + knownFiles[i]) << std::endl;
  }
  std::cout << std::string(WIDTH, WALL) << std::endl;
  std::cout << std::string(INPUT_SEPARATION, '\n') << std::endl;
  std::cin >> option;
  if (option != 1 && option != 2) option = 1;
  filename = knownFiles[option - 1];
  APv.loadFromFile(knownFiles[option - 1]);
  std::cout << "Loaded file: " << knownFiles[option - 1] << std::endl;
  

  while (true) {
    std::system("clear");
    std::cout << std::string(WIDTH, WALL) << std::endl;
    std::cout << std::string((WIDTH - 25) / 2 + 1, WALL) + "STACK AUTOMATON SIMULATOR" + 
        std::string((WIDTH - 25) / 2, WALL)<< std::endl;
    std::cout << std::string(WIDTH, WALL) << std::endl;
    std::cout << tabString("Choose an option:") << std::endl;
    for (int i = 0; i < knownFiles.size(); i++) {
      std::cout << tabString("(" + std::to_string(i + 1) + "): " + 
          "Load " + knownFiles[i]) << std::endl;
    }
    std::cout << tabString(index(1) + "Load other file") << std::endl;
    if (!stepMode) std::cout << tabString(index(2) + "Set stepMode") << std::endl;
    if (stepMode) std::cout << tabString(index(2) + "Unset stepMode") << std::endl;
    std::cout << tabString(index(3) + "Validate input") << std::endl;
    std::cout << tabString(index(4) + "Terminate") << std::endl;
    std::cout << std::string(WIDTH, WALL) << std::endl << std::endl;
    std::cout << "Loaded file: " << filename << std::endl;
    std::cout << (stepMode ? "Step mode active" : "Step mode not active") << std::endl << std::endl;
    APv.logInfo();
    std::cout << "> ";
    std::cin >> option;
    if (option <= knownFiles.size()) {
      APv.loadFromFile(knownFiles[option - 1]);
      filename = knownFiles[option - 1];
    } 
    else {
      option = option - knownFiles.size();
      switch (option) {
        case 1:
          std::cout << "> Enter filename: ";
          std::cin >> filename;
          break;

        case 2:
          stepMode = !stepMode;
          APv.setStepMode(stepMode);
          break;

        case 3:
          std::system("clear");
          APv.loadFromFile(filename);
          APv.setStepMode(stepMode);
          APv.logInfo();
          while (true) {
            std::cout << std::string(WIDTH, WALL) << std::endl;
            std::cout << std::endl << "> Enter input or type \"exit\": ";
            std::cin >> input;
            if (input == "exit") break;
            APv.loadFromFile(filename);
            APv.setStepMode(stepMode);
            std::cout << std::endl << (APv.validateString(input) ? "Result: valid." : "Result: Not valid.") << std::endl;
          }
          break;

          case 4:
            std::system("clear");
            exit(-1);
          break;

          default:
            break;
      }
    }
  }
  exit (-1);
}



