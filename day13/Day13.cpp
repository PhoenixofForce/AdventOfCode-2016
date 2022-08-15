#include "Day13.h"

static int id = std::stoi(getFile(2016, 13));
int main() {  
    Pos start{1, 1, 0};
    Pos end{ a_star::a_star<Pos>(start, addPosses, isEnd) };
    std::cout << end.x << " " << end.y << " in " << end.moves << std::endl;;

    std::vector<Pos> open{};

    open.push_back(start);
    Pos current{start};

    for(int i{0}; i < open.size(); i++) {
        current = open.at(i);
        if(current.moves < -50) {
            std::cout << i << std::endl;
            break;
        }

        std::vector<Pos> newPosses{};
        addPosses(newPosses, current);

        for(Pos p: newPosses) {
            if(std::find(open.begin(), open.end(), p) == open.end()) {
                open.push_back(p);
            }
        }
    }

    return 0;
}

bool isEnd(const Pos& pos) {
    return pos.x == 31 && pos.y == 39;
}

void addPosses(std::vector<Pos>& list, const Pos& current) {
    if(current.x > 0) {
        Pos pos{current.x - 1, current.y, current.moves - 1};
        if(isValid(pos)) {
            list.push_back(pos);
        }
    }
    if(current.y > 0) {
        Pos pos{current.x, current.y - 1, current.moves - 1};
        if(isValid(pos)) {
            list.push_back(pos);
        }
    }

    Pos pos{current.x + 1, current.y, current.moves - 1};
    if(isValid(pos)) {
        list.push_back(pos);
    }

    pos = {current.x, current.y + 1, current.moves - 1};
    if(isValid(pos)) {
        list.push_back(pos);
    }
}

bool isValid(const Pos& pos) {
    int x = pos.x;
    int y = pos.y;

    int out = x * x + 3 * x + 2 * x * y + y + y * y;
    out += id;

    return bitCount(out) % 2 == 0;
}

int bitCount(int n) {

    int counter = 0;
    while(n) {
        counter += n % 2;
        n >>= 1;
    }
    return counter;
 }


namespace std {
size_t hash<Pos>::operator()(const Pos& pos) const{
    size_t hash = 17;
    hash = hash*31 + pos.x;
    hash = hash*31 + pos.y;
    return hash;
  }
}

bool operator<(const Pos& lhs, const Pos& rhs) {
    return lhs.moves/* - heurstic(lhs)*/ < rhs.moves;// - heurstic(rhs);
}

bool operator<=(const Pos& lhs, const Pos& rhs) {
    return lhs.moves/* - heurstic(lhs)*/ <= rhs.moves;// - heurstic(rhs);
}

bool operator>(const Pos& lhs, const Pos& rhs) {
    return lhs.moves/* - heurstic(lhs)*/ > rhs.moves;// - heurstic(rhs);
}

bool operator>=(const Pos& lhs, const Pos& rhs) {
    return lhs.moves/* - heurstic(lhs)*/ >= rhs.moves;// - heurstic(rhs);
}

bool operator==(const Pos& lhs, const Pos& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
