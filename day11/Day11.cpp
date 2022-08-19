#include "Day11.h"

bool compare(const std::vector<std::string>& v1, const std::vector<std::string>& v2)
{
    int leftChips = 0;
    int rightChips = 0;
    int leftGenerator = 0;
    int rightGenerator = 0;

    for(const std::string& element: v1) {
        if(isGenerator(element)) leftGenerator++;
        if(isChip(element)) leftChips++;
    }

    for(const std::string& element: v2) {
        if(isGenerator(element)) rightGenerator++;
        if(isChip(element)) rightChips++;
    }

    return leftGenerator == rightGenerator && leftChips == rightChips;
}

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 11);

    State current{};
    fillFloor(current.floor1, input.at(0));
    fillFloor(current.floor2, input.at(1));
    fillFloor(current.floor3, input.at(2));
    fillFloor(current.floor4, input.at(3));

    bool part2 = true;
    if(part2) {
        current.floor1.push_back("elerium generator");
        current.floor1.push_back("elerium-compatible microchip");
        current.floor1.push_back("dilithium generator");
        current.floor1.push_back("dilithium-compatible microchip");
    }

    std::priority_queue<State> queue{};
    std::unordered_set<State> visited{};
    queue.push(current);

    int moveCount = 1;
    int iterations = 0;
    while(!queue.empty()) {
        current = queue.top();
        queue.pop();

        if(visited.find(current) != visited.end()) continue;
        visited.insert(current);
        
        if(iterations%1000 == 0) {
            std::cout << -current.numberOfMoves << " = " << current.floor1.size() << " " << current.floor2.size() << " " << current.floor3.size() << " " << current.floor4.size() << "; " << iterations << " searched; " << queue.size() << " in queue" << std::endl;
            moveCount = current.numberOfMoves;
        }
        iterations++;

        if(current.floor1.size() == 0 && current.floor2.size() == 0 && current.floor3.size() == 0) {
            print(part2? 2: 1) << -current.numberOfMoves << "; " << iterations << " searched";
            break;
        }

        std::vector<std::string>& currentFloor{getCurrentFloor(current)};

        bool shouldMoveDown{ false };
        for(int i = 0; i < current.elevator; i++) {
            if(getFloor(current, i).size() > 0) {
                shouldMoveDown = true;
                break;
            }
        }

        for(int floorDiv = -1; floorDiv <= 1; floorDiv++) {
            for(int i = 0; i < currentFloor.size(); i++) {
                const std::string& element{ currentFloor.at(i) };
                if((!shouldMoveDown && floorDiv < 0) || floorDiv == 0 || (current.elevator + floorDiv < 0) || (current.elevator + floorDiv > 3)) continue;

                bool moveChip = false;
                bool moveGenerator = false;
                bool moveChipX2 = false;
                bool moveChipGenerator = false;
                bool moveGeneratorX2 = false;

                for(int j = 0; j <= i; j++) {
                    const std::string& element2{ currentFloor.at(j) };

                    if(element != element2) {
                        if(isChip(element) && isChip(element2)) {
                            if(moveChipX2) {
                                continue;
                            } else {
                                moveChipX2 = true;
                            }
                        }

                        else if(isGenerator(element) && isGenerator(element2)) {
                            if(moveGeneratorX2) {
                                continue;
                            } else {
                                moveGeneratorX2 = true;
                            }
                        }

                        else {
                            if(moveChipGenerator) {
                                continue;
                            } else {
                                moveChipGenerator = true;
                            }
                        }
                    } else { // move single element
                        if(isChip(element)) {
                            if(moveChip) {
                                continue;
                            } else {
                                moveChip = true;
                            }
                        }

                        else if(isGenerator(element)) {
                            if(moveGenerator) {
                                continue;
                            } else {
                                moveGenerator = true;
                            }
                        }
                    }

                    State copy = current;
                    copy.numberOfMoves -= 1;
                    std::vector<std::string>& oldFloor{ getCurrentFloor(copy) };
                    copy.elevator += floorDiv;
                    std::vector<std::string>& newFloor{ getCurrentFloor(copy) };

                    oldFloor.erase(std::remove(oldFloor.begin(), oldFloor.end(), element), oldFloor.end());
                    newFloor.push_back(element);

                    if(element != element2) {
                        oldFloor.erase(std::remove(oldFloor.begin(), oldFloor.end(), element2), oldFloor.end());
                        newFloor.push_back(element2);
                    }

                    if(validState(copy) && visited.find(copy) == visited.end()) queue.push(copy);
                }
            }
        }
    }

    return 0;
}

bool validState(const State& state) {
    return validFloor(state.floor1) && validFloor(state.floor2) && 
            validFloor(state.floor3) && validFloor(state.floor4);
}

bool validFloor(const std::vector<std::string>& floor) {
    std::vector<std::string> generators{};

    for(const std::string& element: floor) {
        if(isGenerator(element)) {
            generators.push_back(element);
        }
    }
    
    if(generators.size() == 0) return true;

    for(const std::string& element: floor) {
        if(isChip(element)) {
            std::string type{ element.substr(0, element.find("-co")) };
            
            bool containsGenerator = false;
            for(const std::string& generator: generators) {
                if(generator.find(type) != std::string::npos) {
                    containsGenerator = true;
                    break;
                }
            }
            if(!containsGenerator) return false;
        }
    }

    return true;
}

bool isGenerator(const std::string& part) {
    return part.find("generator") != std::string::npos;
}
bool isChip(const std::string& part) {
    return part.find("microchip") != std::string::npos;
}

/*
The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.
The second floor contains a hydrogen generator.
The third floor contains a lithium generator.
The fourth floor contains nothing relevant.
*/
void fillFloor(std::vector<std::string>& floor, const std::string& line) {
    std::string replacedLine{ std::regex_replace(line, std::regex{"(\\.|, and| and)"}, ",") };
    std::cout << replacedLine << std::endl;
    while(replacedLine.find(" a ") != std::string::npos) {
        size_t start = replacedLine.find(" a ") + 3;
        std::string element{ replacedLine.substr(start, replacedLine.find(",") - start) };
        replacedLine = replacedLine.substr(start + element.size() + 1);

        floor.push_back(element);
    }
}

std::vector<std::string>& getCurrentFloor(State& current) {
    return getFloor(current, current.elevator);
}

std::vector<std::string>& getFloor(State& current, int floor) {
    return  (floor == 0? current.floor1:
            (floor == 1? current.floor2:
            (floor == 2? current.floor3: 
                         current.floor4)));
}



bool operator<(const State& lhs, const State& rhs) {
    return lhs.numberOfMoves - heurstic(lhs) < rhs.numberOfMoves - heurstic(rhs);
}

bool operator==(const State& lhs, const State& rhs) {
    return compare(lhs.floor1, rhs.floor1) && 
            compare(lhs.floor2, rhs.floor2) && 
            compare(lhs.floor3, rhs.floor3) && 
            compare(lhs.floor4, rhs.floor4) && 
            lhs.elevator == rhs.elevator;
}

int heurstic(const State& state) {
    return std::ceil(state.floor1.size() / 2.0) * 3 + 
            std::ceil(state.floor2.size() / 2.0) * 2 +
            std::ceil(state.floor3.size() / 2.0) * 1 -
            state.floor4.size();
}

size_t std::hash<State>::operator()(const State &state) const{
    // computes the hash of an employee using a variant 
    // of the Fowler-Noll-Vo hash function
    size_t result = 2166136261;

    std::vector<std::string> list = state.floor1;
    std::sort(list.begin(), list.end());
    for(const std::string& s: list) {
        for (size_t i = 0, ie = s.size(); i != ie; ++i) {
            result = (result * 16777619) ^s[i];
        }
    }

    list = state.floor2;
    std::sort(list.begin(), list.end());
    for(const std::string& s: list) {
        for (size_t i = 0, ie = s.size(); i != ie; ++i) {
            result = (result * 16777619) ^s[i];
        }
    }

    list = state.floor3;
    std::sort(list.begin(), list.end());
    for(const std::string& s: list) {
        for (size_t i = 0, ie = s.size(); i != ie; ++i) {
            result = (result * 16777619) ^s[i];
        }
    }

    list = state.floor4;
    std::sort(list.begin(), list.end());
    for(const std::string& s: list) {
        for (size_t i = 0, ie = s.size(); i != ie; ++i) {
            result = (result * 16777619) ^s[i];
        }
    }

    return result ^ (state.elevator << 1);
}
