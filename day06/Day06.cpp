#include "Day06.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 06);
    int length = input.at(0).size();

    std::vector<std::vector<Letter>> letters{};
    for(int i = 0; i < length; i++) letters.push_back({});

    for(std::string line: input) {
        for(int i = 0; i < length; i++) {
            std::vector<Letter>& letterList = letters.at(i);

            char c = line.at(i);

            auto pos = std::find_if(letterList.begin(), letterList.end(), [c](const Letter& l) -> bool {
                return l.c == c;
            });

            if(pos != letterList.end()) {
                letterList.at(std::distance(letterList.begin(), pos)).count++;
            } else {
                letterList.push_back({c, 1});
            }
        }
    }

    for(int i = 0; i < length; i++) {
        std::vector<Letter>& letterList = letters.at(i);
        std::sort(letterList.begin(), letterList.end(), [](const Letter& a, const Letter& b) -> bool {
            if(a.count == b.count) return a.c < b.c;
            else return a.count > b.count;
        });

        std::cout << letterList.at(0).c;
    }
    std::cout << std::endl;

    for(int i = 0; i < length; i++) {
        std::vector<Letter>& letterList = letters.at(i);
        std::cout << letterList.at(letterList.size() - 1).c;
    }
    std::cout << std::endl;

    return 0;
}