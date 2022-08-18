#include "Day24.h"

static int maxX{};
static int maxY{};

static Pos goal{};
static std::map<Pos, bool> maze{}; //true if wall

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 24);


    std::map<Pos, int> shortestPaths{};
    Pos specialPositions[8]{};

    for(int y{0}; y < input.size(); y++) {
        const std::string& line{ input.at(y) };
        for(int x{0}; x < line.size(); x++) {
            char c{ line.at(x) };

            Pos pos{x, y};
            if(c >= '0' && c <= '7') {
                specialPositions[std::stoi(std::string{ c })] = pos;
            }
            maze[pos] = (c == '#');

            if(x > maxX) maxX = x;
        }
        if(y > maxY) maxY = y;
    }

    for(int from{ 0 }; from < 8; from++) {
        Path start{ specialPositions[from], 0 };
        for(int to{ 0 }; to < 8; to++) {
            if(from == to) continue;
            goal = specialPositions[to];
            shortestPaths[{from, to}] = -a_star::a_star<Path>( start, addStates, isEnd, false).moves;
            std::cout << shortestPaths[{from, to}] << " for path from " << from << " to " << to << std::endl;
        }
    }

    int out{ 999999999 };
    int out2{ 999999999 };
    int start{};
    for(int first = 1; first < 8; first++) {
        int start2first{ shortestPaths[{start, first}] };

        for(int second = 1; second < 8; second++) {
            if(first == second) continue;
            int first2second{ shortestPaths[{first, second}] };

            for(int third = 1; third < 8; third++) {
                if(first == third ||second == third) continue;
                int second2third{ shortestPaths[{second, third}] };

                for(int fourth = 1; fourth < 8; fourth++) {
                    if(first == fourth ||second == fourth || third == fourth) continue;
                    int third2fourth{ shortestPaths[{third, fourth}] };

                    for(int fift = 1; fift < 8; fift++) {
                        if(first == fift ||second == fift || third == fift || fourth == fift) continue;
                        int fourth2fift{ shortestPaths[{fourth, fift}] };

                        for(int sixt = 1; sixt < 8; sixt++) {
                            if(first == sixt ||second == sixt || third == sixt || fourth == sixt || fift == sixt) continue;
                            int fift2sixt{ shortestPaths[{fift, sixt}] };
                            
                            for(int seventh = 1; seventh < 8; seventh++) {
                                if(first == seventh ||second == seventh || third == seventh || fourth == seventh || fift == seventh || sixt == seventh) continue;
                                int sixt2seventh{ shortestPaths[{sixt, seventh}] };
                                int seventh2start{ shortestPaths[{seventh, start}] };

                                int length{ start2first + first2second + second2third + third2fourth + fourth2fift + fift2sixt + sixt2seventh };
                                int length2{ start2first + first2second + second2third + third2fourth + fourth2fift + fift2sixt + sixt2seventh + seventh2start };
                                if(length < out) {
                                    out = length;
                                    std::cout << "1: " << start << " - "<< first << " - "<< second << " - "<< third << " - "<< fourth << " - "<< fift << " - "<< sixt << " - " << seventh << " == " << length << std::endl;
                                }
                                if(length2 < out2) {
                                    out2 = length2;
                                    std::cout << "2: " << start << " - "<< first << " - "<< second << " - "<< third << " - "<< fourth << " - "<< fift << " - "<< sixt << " - " << seventh << " - " << start << " == " << length2 << std::endl;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    print() << out << std::endl;
    print() << out2 << std::endl;

    return 0;
}

bool isEnd(const Path& state) {
    return state.current == goal;
}

void addStates(std::vector<Path>& list, const Path& current) {
    Pos pos{ current.current };
    if(pos.x > 0) {
        Pos nextPos{ pos.x - 1, pos.y };
        if(!maze.at(nextPos)) {
            list.push_back( { nextPos, current.moves-1 } );
        }
    }

    if(pos.x < maxX) {
        Pos nextPos{ pos.x + 1, pos.y };
        if(!maze.at(nextPos)) {
            list.push_back( { nextPos, current.moves-1 } );
        }
    }

    if(pos.y > 0) {
        Pos nextPos{ pos.x, pos.y - 1 };
        if(!maze.at(nextPos)) {
            list.push_back( { nextPos, current.moves-1 } );
        }
    }

    if(pos.y < maxY) {
        Pos nextPos{ pos.x, pos.y + 1 };
        if(!maze.at(nextPos)) {
            list.push_back( { nextPos, current.moves-1 } );
        }
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

size_t std::hash<Path>::operator()(const Path& state) const { 
    size_t out{17};
    out = out * 31 + state.current.x;
    out = out * 31 + state.current.y;
    return out;
} 
bool operator<(const Path& lhs, const Path& rhs) {
    return lhs.moves < rhs.moves;
}
bool operator==(const Path& lhs, const Path& rhs) {
    return lhs.current == rhs.current;
}
