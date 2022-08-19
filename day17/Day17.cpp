#include "Day17.h"

static std::string id{ getFile(2016, 17) };

int main() {
    std::cout << id;
    State start{0, 0, ""};
    State solution1{ a_star::a_star<State>(start, addStates, isEnd, true, true) };
    print() << solution1.path << " " << solution1.path.size() << std::endl;
    State solution2{ a_star::a_star<State>(start, addStates, isEnd, false, false) };
    print() << solution2.path << " " << solution2.path.size() << std::endl;

    return 0;
}

bool isEnd(const State& state) {
    bool out = state.x == 3 && state.y == 3;
    return out;
}

void addStates(std::vector<State>& list, const State& current) {
    std::string doors{ md5(id + current.path).substr(0, 4) };

    if(doors.at(0) > 'a') {
        State state{current.x, current.y - 1, current.path + "U", current.moves - 1};
        if(isValid(state)) list.push_back(state);
    }

    if(doors.at(1) > 'a') {
        State state{current.x, current.y + 1, current.path + "D", current.moves - 1};
        if(isValid(state)) list.push_back(state);
    }

    if(doors.at(2) > 'a') {
        State state{current.x - 1, current.y, current.path + "L", current.moves - 1};
        if(isValid(state)) list.push_back(state);
    }

    if(doors.at(3) > 'a') {
        State state{current.x + 1, current.y, current.path + "R", current.moves - 1};
        if(isValid(state)) list.push_back(state);
    }
}

bool isValid(const State& state) {
    int x = state.x;
    int y = state.y;
    return x >= 0 && x < 4 &&
            y >= 0 && y < 4;
}


size_t std::hash<State>::operator()(const State &state) const {
    std::hash<std::string> hasher{};

    size_t hash = 17;
    hash = hash*31 + state.x;
    hash = hash*31 + state.y;
    hash = hash*31 + hasher(md5(id + state.path).substr(0, 4));
    return hash;
}


bool operator<(const State& lhs, const State& rhs) {
    return lhs.moves < rhs.moves;
}

bool operator==(const State& lhs, const State& rhs) {
    return false;/*lhs.x == rhs.x &&
            lhs.y == rhs.y &&
            md5(id + lhs.path).substr(0, 4) == md5(id + rhs.path).substr(0, 4);*/
}