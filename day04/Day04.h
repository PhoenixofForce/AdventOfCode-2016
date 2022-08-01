#ifndef DAYXX_H
#define DAYXX_H

#include "../Utils.h"
#include <iostream>
#include <vector>
#include <algorithm>

struct Letter {
    char c{' '};
    int count{};
};

int sectorId(const std::string& line);
std::string decrypt(const std::string& line, int sectorId);

#endif