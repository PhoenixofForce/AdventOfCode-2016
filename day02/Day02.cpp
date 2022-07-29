#include "Day02.h"

int main() {
    std::vector<std::string> lines;
    getLines(lines, 2016, 02);

    char numpad[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
    for(std::string& line: lines) {
        std::cout << findButton(numpad, 3, 1, 1, line);
    }

    std::cout << std::endl;

    char numpad2 [5][5] = {{' ', ' ', '1', ' ', ' '}, {' ', '2', '3', '4', ' '}, {'5', '6', '7', '8', '9'}, {' ', 'A', 'B', 'C', ' '}, {' ', ' ', 'D', ' ', ' '}};
    for(std::string& line: lines) {
        std::cout << findButton(numpad2, 5, 0, 2, line);
    }

    return 0;
}

template <size_t size_x, size_t size_y>
char findButton(char (&keyPad)[size_x][size_y], int arrayLength, int startX, int startY, std::string& line) {
    int x{ startX };
    int y{ startY };

    for(int i = 0; i < line.length(); i++) {
        char dir{ line.at(i) };

        if(dir == 'U' && y > 0 && keyPad[y-1][x] != ' ') y--;
        if(dir == 'D' && y < arrayLength - 1 && keyPad[y+1][x] != ' ') y++;
        if(dir == 'L' && x > 0 && keyPad[y][x-1] != ' ') x--;
        if(dir == 'R' && x < arrayLength - 1 && keyPad[y][x+1] != ' ') x++;
    }

    return keyPad[y][x];
}