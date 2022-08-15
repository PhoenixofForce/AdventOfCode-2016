#ifndef DAYXX_H
#define DAYXX_H

#include "../Utils.h"
#include <iostream>

struct disc {
    int currentPosition{};
    int totalPositions{};
};

disc string2disc(const std::string& line);
bool checkState(int t, std::vector<disc>& input);

#endif