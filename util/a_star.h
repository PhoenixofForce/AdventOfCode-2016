#ifndef A_STAR_H
#define A_STAR_H

#include <iostream>
#include <unordered_set>
#include <vector>
#include <queue>

/*

bool isEnd(const State& state);
void addStates(std::vector<State>& list, const State& current);

*/

namespace a_star {

template <typename State>
State a_star(
    const State& start, 
    void (*generator) (std::vector<State>&, const State&), 
    bool (*confirmer) (const State&)) {

    std::priority_queue<State> queue{};
    std::unordered_set<State> visited{};
    queue.push(start);

    int iterations{};   
    while (!queue.empty()) {
        State current{ queue.top() };
        queue.pop();

        if(visited.find(current) != visited.end()) continue;
        visited.insert(current);

        if(iterations%1000 == 0) {
            std::cout << iterations << " searched; " << queue.size() << " in queue" << std::endl;
        }
        iterations++;

        if(confirmer(current)) {
            return current;
        }

        std::vector<State> newStates{};
        generator(newStates, current);
        for(State s: newStates) {
            if(visited.find(s) == visited.end()) queue.push(s);
        }
    }
    
    return start;
}

};

#endif