#ifndef DAY24_H
#define DAY24_H

#include "../Utils.h"
#include "../util/a_star.h"
#include <iostream>

struct Pos {
    int x{};
    int y{};
};
bool operator<(const Pos& l, const Pos& r);
bool operator==(const Pos& l, const Pos& r);
bool operator!=(const Pos& l, const Pos& r);

struct Path {
    Pos current{};
    int moves{};
};

bool isEnd(const Path& state);
void addStates(std::vector<Path>& list, const Path& current);

template <>
class std::hash<Path> {
 public:
  size_t operator()(const Path &state) const;
};

bool operator<(const Path& lhs, const Path& rhs);
bool operator==(const Path& lhs, const Path& rhs);

#endif