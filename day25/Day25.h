#ifndef DAY25_H
#define DAY25_H

#include "../Utils.h"
#include <iostream>
#include <regex>

#define THRESHOLD 10000

bool testInput(const std::vector<std::string> lines, int a);
void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty = true);
int toValue(const std::map<std::string, int>& registry, const std::string& valueName);

#endif