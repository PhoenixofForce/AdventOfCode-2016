#include "Day08.h"

int main() {
    std::vector<std::string> lines{};
    getLines(lines, 2016, 8);

    bool screen[6][50]{{},{},{},{},{},{}};

    for(std::string& line: lines) {
        if(line.find("rect") == 0) {
            std::string rectCoords{line.substr(5)};
            int w{std::stoi(rectCoords.substr(0, rectCoords.find("x")))};
            int h{std::stoi(rectCoords.substr(rectCoords.find("x") + 1))};

            for(int y{0}; y < h; y++) {
                for(int x{0}; x < w; x++) {
                    if(x >= 0 && x < 50 && y >= 0 && y < 6)
                        screen[y][x] = true;
                }
            }
        }

        if(line.find("rotate column") == 0) {
            std::string args{line.substr(16)};
            int x{std::stoi(args.substr(0, args.find(" ")))};
            int by{std::stoi(args.substr(args.find("by") + 3))};

            bool col[6]{};
            for(int y{0}; y < 6; y++) {
                int ny{y - by};
                if(ny < 0) ny += 6;

                col[y] = screen[ny][x];
            }

            for(int y{0}; y < 6; y++) {
                screen[y][x] = col[y];
            }
        }

        if(line.find("rotate row") == 0) {
            std::string args{line.substr(13)};
            int y{std::stoi(args.substr(0, args.find(" ")))};
            int by{std::stoi(args.substr(args.find("by") + 3))};

            bool row[50]{};
            for(int x{0}; x < 50; x++) {
                int nx{x - by};
                if(nx < 0) nx += 50;
                row[x] = screen[y][nx] ;
            }

            for(int x{0}; x < 50; x++) {
                screen[y][x] = row[x];
            }
        }

        std::cout << line << std::endl;
        for(int y{0}; y < 6; y++) {
            for(int x{0}; x < 50; x++) {
                std::cout << (screen[y][x]? "#": ".");
            }
            std::cout << std::endl;
        }   
        std::cout << std::endl << std::endl;
    } 
    
    int out{0}; 
    for(int y{0}; y < 6; y++) {
        for(int x{0}; x < 50; x++) {
            if(screen[y][x]) out++;
        }
    }
    std::cout << out;

    return 0;
}