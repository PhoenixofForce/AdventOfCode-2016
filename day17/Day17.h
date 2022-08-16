#ifndef DAY17_H
#define DAY17_H

#include "../Utils.h"
#include "../util/a_star.h"
#include "../util/md5.h"

#include <iostream>

struct State {
    int x{};
    int y{};
    std::string path{};
    int moves{};
};

namespace std {
template <>
class hash<State> {
 public:
  size_t operator()(const State &state) const;
};
}

bool operator<(const State& lhs, const State& rhs);
bool operator<=(const State& lhs, const State& rhs);
bool operator>(const State& lhs, const State& rhs);
bool operator>=(const State& lhs, const State& rhs);
bool operator==(const State& lhs, const State& rhs);

bool isEnd(const State& state);
void addStates(std::vector<State>& list, const State& current);
bool isValid(const State &state);

#endif