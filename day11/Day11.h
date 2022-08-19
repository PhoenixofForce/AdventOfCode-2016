#ifndef DAY11_H
#define DAY11_H

#include "../Utils.h"
#include <iostream>
#include <queue>
#include <regex>
#include <algorithm>
#include <cmath>
#include <unordered_set>

struct State {
    int numberOfMoves{};
    std::vector<std::string> floor1{};
    std::vector<std::string> floor2{};
    std::vector<std::string> floor3{};
    std::vector<std::string> floor4{};
    int elevator{};
};

template <>
class std::hash<State> {
 public:
  size_t operator()(const State &state) const;
};


bool operator<(const State& lhs, const State& rhs);
bool operator==(const State& lhs, const State& rhs);
int heurstic(const State& state);

bool validState(const State& state);
bool validFloor(const std::vector<std::string>& floor);

bool isGenerator(const std::string& part);
bool isChip(const std::string& part);

void fillFloor(std::vector<std::string>& floor, const std::string& line);
std::vector<std::string>& getCurrentFloor(State& current);
std::vector<std::string>& getFloor(State& current, int floor);

#endif