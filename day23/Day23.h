#ifndef DAY23_H
#define DAY23_H

#include "../Utils.h"
#include <iostream>
#include <regex>

void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty = true);
int toValue(const std::map<std::string, int>& registry, const std::string& valueName);

#endif