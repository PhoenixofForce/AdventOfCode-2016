#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

/*
#include "../util/a_star.h"

bool isEnd(const State& state);
void addStates(std::vector<State>& list, const State& current);

template <>
class std::hash<State> {
 public:
  size_t operator()(const State &state) const;
};

size_t std::hash<State>::operator()(const State &state) const { } 

bool operator<(const State& lhs, const State& rhs)  {
    return lhs.moves - heuristic(lhs) < rhs.moves - heuristic(rhs); //A*
    return lhs.moves < rhs.moves; //Dijkstra
}

bool operator==(const State& lhs, const State& rhs);

*/

template<typename T>
using StateGenerator = void(*)(std::vector<T>&, const T&);

template<typename T>
using StateConfirmer= bool(*)(const T&);

namespace a_star {

/** Finds the shortest path
  * @param start the first State from which you want to find an end state
  * @param generator a function which generates states that can be reached from a given state
  * @param confirmer a function  that returns true, when a given state is a desired goal
  * @param doOuput should optional debug outputs be made? (default: true)
  * @param returnFirst should the search return the first found (aka shortest) path? if false it returns the last found (aka longest) path (default: true)
  * @return the found end state
  */
template <typename State>
State a_star(const State& start, StateGenerator<State> generator, StateConfirmer<State> confirmer, bool doOutput = true, bool returnFirst = true) {

    std::priority_queue<State> queue{};
    std::unordered_set<State> visited{};
    queue.push(start);

    int iterations{};   
    State last{ start };
    while (!queue.empty()) {
        State current{ queue.top() };
        queue.pop();

        if(visited.find(current) != visited.end()) continue;
        visited.insert(current);

        if(iterations%1000 == 0) {
            if(doOutput) std::cout << iterations << " searched; " << queue.size() << " in queue" << std::endl;
        }
        iterations++;

        if(confirmer(current)) {
            if(returnFirst) return current;
            last = current;
            continue;
        }

        std::vector<State> newStates{};
        generator(newStates, current);
        for(State s: newStates) {
            if(visited.find(s) == visited.end()) queue.push(s);
        }
    }
    
    return last;
}

};

#endif