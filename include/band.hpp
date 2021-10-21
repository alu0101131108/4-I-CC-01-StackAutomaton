#ifndef __BAND_H__
#define __BAND_H__

#include <iostream>
#include <vector>
#include <string>

class Band {
  private:
    int headIndex;
    std::vector<std::string> content;
    std::vector<std::string> alphabet;

  public:
    Band();
    void setAlphabet(std::vector<std::string> newAlphabet);
    void addToAlphabet(std::string symbol);
    void setContent(std::vector<std::string> newContent);
    void addToContent(std::string symbol);
    void consume(int steps);
    void checkInAlphabet(std::string symbol);
    std::string getHead();
    void logAlphabet();
    void logContent();
    void clear();
    bool empty();
  
};

#endif // __BAND_H__