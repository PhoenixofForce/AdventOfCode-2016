#include "Day22.h"

static int maxX{};
static int maxY{};

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 22);
    input.erase(input.begin(), input.begin() + 2);

    std::map<Pos, Server> servers{};

    Pos emptyStartPos{};
    Pos goalPos{};

    for(std::string& line: input) {
        line = std::regex_replace(line, std::regex{"\\s+"}, " ");

        std::vector<std::string> splitLine{};
        split(splitLine, line, " ", true);

        auto xStart{ splitLine.at(0).find("x") + 1 };
        auto yStart{ splitLine.at(0).find("y") };
        auto yEnd{ line.find(" ") };

        int x = std::stoi(splitLine.at(0).substr(xStart, yStart - xStart - 1));
        int y = std::stoi(splitLine.at(0).substr(yStart + 1));

        if(x > maxX) maxX = x;
        if(y > maxY) maxY = y;

        std::string placeholder{ std::regex_replace(splitLine.at(1), std::regex{"T"}, "") }; 
        int size = std::stoi(placeholder);

        placeholder = std::regex_replace(splitLine.at(2), std::regex{"T"}, ""); 
        int used = std::stoi(placeholder);

        placeholder = std::regex_replace(splitLine.at(3), std::regex{"T"}, ""); 
        int avail = std::stoi(placeholder);

        if(used == 0) {
            emptyStartPos.x = x;
            emptyStartPos.y = y;
        }

        Pos pos{x , y};
        Server server{size, used, avail};

        servers[pos] = server;
    }
    goalPos.x = maxX;

    int out = 0;
    for (const auto &[pos1, server1]: servers) {
        for (const auto &[pos2, server2]: servers) {
            if(pos1 != pos2 && server1.used > 0 && server1.used <= server2.avail) out++;
        }
    }
    print() << out << std::endl;

    State start{ servers, emptyStartPos, goalPos, 0 };
    State end = a_star::a_star<State>(start, addStates, isEnd);
    print() << -end.moves;

    return 0;
}

void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty) {
    int pos = 0;
    while(toSplit.find(delim, pos) != std::string::npos) {
        int newPos = toSplit.find(delim, pos);
        std::string toPush = toSplit.substr(pos, newPos - pos);
        if(!filterEmpty || toPush.size() > 0) list.push_back(toPush);
        pos = newPos + delim.size();
    }
    if(pos < toSplit.size()) {
        std::string toPush = toSplit.substr(pos);
        if(!filterEmpty || toPush.size() > 0) list.push_back(toPush);
    }
}

bool isEnd(const State& state) {
    return state.goalPos.x == 0 && state.goalPos.y == 0;
}

void addStates(std::vector<State>& list, const State& current) {
    const Pos& emptyPos{ current.emptyPos };

    if(emptyPos.x > 0) {
        singleState(list, current, -1, 0);
    }

    if(emptyPos.x < maxX) {
        singleState(list, current, 1, 0);
    }

    if(emptyPos.y > 0) {
        singleState(list, current, 0, -1);
    }

    if(emptyPos.y < maxY) {
        singleState(list, current, 0, 1);
    }
}

void singleState(std::vector<State>& list, const State& current, int dx, int dy) {
    const std::map<Pos, Server>& servers{ current.servers };
    const Pos& emptyPos{ current.emptyPos };
    const Pos& goalPos{ current.goalPos };

    const Server& emptyServer{ servers.at(emptyPos) };
    
    Pos otherPos{ emptyPos.x + dx, emptyPos.y + dy };
    const Server& otherServer{ servers.at(otherPos) };

    if(emptyServer.avail >= otherServer.used) {
        State clone = current;
        clone.servers.at(emptyPos).used = servers.at(otherPos).used;
        clone.servers.at(emptyPos).avail = clone.servers.at(emptyPos).maxSize - clone.servers.at(emptyPos).used;
        clone.servers.at(otherPos).used = 0;
        clone.servers.at(otherPos).avail = clone.servers.at(otherPos).maxSize;

        if(otherPos == goalPos) {
            clone.goalPos.x = emptyPos.x;
            clone.goalPos.y = emptyPos.y;
        }

        clone.emptyPos.x = otherPos.x;
        clone.emptyPos.y = otherPos.y;

        clone.moves--;

        list.push_back(clone);
    }
}

bool operator<(const Pos& l, const Pos& r) {
    return (l.x<r.x || (l.x==r.x && l.y<r.y)); 
}

bool operator==(const Pos& l, const Pos& r) {
    return l.x == r.x && l.y == r.y; 
}

bool operator!=(const Pos& l, const Pos& r) {
    return !(l == r); 
}

size_t std::hash<State>::operator()(const State &state) const {
    size_t hash = 17;
    hash = hash*31 + state.goalPos.x;
    hash = hash*31 + state.goalPos.y;
    hash = hash*31 + state.emptyPos.x;
    hash = hash*31 + state.emptyPos.y;
    return hash;
}

int heuristic(const State& state) {
    int emptyGoalDiff = std::abs(state.goalPos.x - state.emptyPos.x) + std::abs(state.goalPos.y - state.emptyPos.y);
    emptyGoalDiff -= 1;

    int goal00Diff = std::abs(state.goalPos.x) + std::abs(state.goalPos.y);

    return emptyGoalDiff + goal00Diff * 5;
}

bool operator<(const State& lhs, const State& rhs) {
    return lhs.moves - heuristic(lhs) < rhs.moves - heuristic(rhs);
}
bool operator==(const State& lhs, const State& rhs) {
    return lhs.emptyPos == rhs.emptyPos && lhs.goalPos == rhs.goalPos;
}