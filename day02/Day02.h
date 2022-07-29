#ifndef DAY02_H
#define DAY02_H

#include "../Utils.h"
#include <iostream>

template <size_t size_x, size_t size_y>
char findButton(char (&keyPad)[size_x][size_y], int arrayLength, int startX, int startY, std::string& line);

#endif