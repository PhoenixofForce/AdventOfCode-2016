#ifndef DAY22_H
#define DAY22_H

#include "../Utils.h"
#include <iostream>
#include <regex>

#include "../util/a_star.h"

struct Pos {
    int x{};
    int y{};
};
bool operator<(const Pos& l, const Pos& r);
bool operator==(const Pos& l, const Pos& r);
bool operator!=(const Pos& l, const Pos& r);

struct Server {
    int maxSize{};
    int used{};
    int avail{};
};

struct State {
    std::map<Pos, Server> servers{};
    Pos emptyPos{};
    Pos goalPos{};
    int moves{};
};

int heuristic(const State& state);

template <>
class std::hash<State> {
 public:
  size_t operator()(const State &state) const;
};


bool operator<(const State& lhs, const State& rhs);
bool operator==(const State& lhs, const State& rhs);

void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty);

bool isEnd(const State& state);
void addStates(std::vector<State>& list, const State& current);
void singleState(std::vector<State>& list, const State& current, int dx, int dy);

#endif