#include "Day18.h"

int main() {
    bool part2 = true;
    int maxRows = part2? 400000: 40;

    std::string input{ getFile(2016, 18) };
    std::vector<std::string> rows{};
    rows.push_back(input);

    while(rows.size() < maxRows) {
        rows.push_back(genNextRow(rows.at(rows.size() - 1)));
    }

    int out = 0; 
    for(const std::string& line: rows) {
        for(char c: line) {
            if(c == '.') out++;
        }
    }
    print(part2? 2: 1) << out << std::endl;

    return 0;
}

std::string genNextRow(const std::string& currentRow) {
    std::string out{};
    for(int i{0}; i < currentRow.size(); i++) {
        bool leftTrap = i > 0 && currentRow.at(i - 1) == '^';
        bool centerTrap = currentRow.at(i) == '^';
        bool rightTrap = i < currentRow.size() - 1 && currentRow.at(i + 1) == '^';

        bool nextTrap = (leftTrap && !centerTrap && !rightTrap) ||
                        (!leftTrap && !centerTrap && rightTrap) ||
                        (leftTrap && centerTrap && !rightTrap) ||
                        (!leftTrap && centerTrap && rightTrap);
        out += (nextTrap? '^': '.');
    }
    return out;
}