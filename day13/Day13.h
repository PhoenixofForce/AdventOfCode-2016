#ifndef DAYXX_H
#define DAYXX_H

#include "../Utils.h"
#include "../util/a_star.h"
#include <iostream>
#include <algorithm>

struct Pos {
    int x{};
    int y{};
    int moves{};
};

template <>
class std::hash<Pos> {
 public:
  size_t operator()(const Pos &state) const;
};

bool operator<(const Pos& lhs, const Pos& rhs);
bool operator==(const Pos& lhs, const Pos& rhs);

bool isEnd(const Pos& pos);
void addPosses(std::vector<Pos>& list, const Pos& current);

bool isValid(const Pos& pos);
int bitCount(int n); 

#endif