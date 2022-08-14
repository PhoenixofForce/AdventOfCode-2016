#ifndef DAY12_H
#define DAY12_H

#include "../Utils.h"
#include <iostream>
#include <chrono>
#include <thread>

void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty = true);
int toValue(const std::map<std::string, int>& registry, const std::string& valueName);

#endif