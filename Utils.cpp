#include "Utils.h"

std::string& trim(std::string& str) {
    std::regex r("(^\\W+|\\W+$)");
    str = std::regex_replace(str, r, "");
    return str;
}

std::string getFileName(int year, int day) {
    std::string out{std::to_string(year) + "inputs/day" + (day > 9? std::to_string(day): "0" + std::to_string(day)) + ".txt" };
    return { out };
}

std::ifstream getReader(int year, int day) {
  std::ifstream f;
  std::cout << getFileName(year, day) << std::endl;
  f.open(getFileName(year, day));
  return f;
}

std::string getFile(int year, int day){
  std::string out;
  std::ifstream f{getReader(year, day)};

  std::string line;
  while(std::getline(f, line)) {
    out += line;
  }
  f.close();

  return out;
}

void getLines(std::vector<std::string>& list, int year, int day) {
  std::ifstream f = getReader(year, day);

  std::string line;
  while(std::getline(f, line)) {
    list.push_back(line);
  }
  f.close();
}

/*
template<typename T>
void getLines(std::vector<T>& list, int year, int day, T parser(const std::string&)) {
  std::ifstream f = getReader(year, day);

  std::string line;
  while(std::getline(f, line)) {
    list.push_back(parser(line));
  }
  f.close();
}*/

void getParagraphs(std::vector<std::string>& list, int year, int day){
  std::ifstream f = getReader(year, day);

  std::string line;
  std::string current;
  while(std::getline(f, line)) {
    if(line.length() == 0) {
      list.push_back(trim(current));
      current = "";

      continue;
    }

    current += line + " ";
  }

  if(current.length() > 0) list.push_back(trim(current));
}

/*
template<typename T>
void getParagraphs(std::vector<T>& list, int year, int day, T parser(const std::string&)) {
  std::ifstream f = getReader(year, day);

  std::string line;
  std::string current;
  while(std::getline(f, line)) {
    if(line.length() == 0) {
      list.push_back(parser(trim(current)));
      current = "";

      continue;
    }

    current += line + " ";
  }

  if(current.length() > 0) list.push_back(parser(trim(current)));
}*/