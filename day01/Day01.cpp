#include "Day01.h"

int main() {
    std::string input { getFile(2016, 1) };
    input += ",";

    int dir = 0; // N E S W
    int x = 0;
    int y = 0;

    std::vector<Pos> positions{};
    bool part2 = false;

    size_t pos = 0;
    while((pos = input.find(",")) != std::string::npos) {
        std::string line{ input.substr(0, pos) };
        while(line.at(0) == ' ') line.erase(0, 1);

        if(line.at(0) == 'L') dir--;
        if(line.at(0) == 'R') dir++;
        while(dir < 0) dir += 4;
        dir %= 4;

        int num{ std::stoi(line.substr(1)) };

        for(int i = 0; i < num; i++) {
            if(dir == 0) y++;
            if(dir == 2) y--;
            if(dir == 1) x++;
            if(dir == 3) x--;
        
            Pos current{x, y};

            if(!part2 && std::find_if(positions.begin(), positions.end(), 
            [&c = current](const Pos& p) -> bool { return c.x == p.x && c.y == p.y; })
            != positions.end()) {
                part2 = true;
                std::cout << "PART 2: " << std::endl;
                print(2) << "x: " << x << std::endl << "y: " << y << std::endl << "res: " << std::abs(x) + std::abs(y) << std::endl; 
            } else {
                positions.push_back(current);
            }
        }
        input.erase(0, pos + 1);
    }

    std::cout << "PART1: " << std::endl;
    print(1) << "x: " << x << std::endl << "y: " << y << std::endl << "res: " << std::abs(x) + std::abs(y) << std::endl;

    return 0;
}