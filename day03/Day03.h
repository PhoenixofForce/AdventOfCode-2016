#ifndef DAY03_H
#define DAY03_H

#include "../Utils.h"

#include <iostream>
#include <algorithm>
#include <vector>

struct Triangle {
    int a{};
    int b{};
    int c{};
};

Triangle line2Triangle(const std::string& lineIn);
bool checkTriangle(const Triangle& triangle);

#endif