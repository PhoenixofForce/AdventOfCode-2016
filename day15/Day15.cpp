#include "Day15.h"

int main() {
    bool part2 = true;

    std::vector<disc> input{};
    getLines<disc>(input, 2016, 15, string2disc);
    if(part2) input.push_back({0, 11});

    int t = 0;
    bool done = false;
    while(!done) {
        if(checkState(t, input)) {
            done = true;
            print() << t;
        }
        t++;
    }

    return 0;
}

disc string2disc(const std::string& line) {
    int totalStart = line.find("has") + 4;
    std::string total = line.substr(totalStart, line.find("positions") - totalStart);

    int currentStart = line.find("position ") + 9;
    std::string current = line.substr(currentStart, line.find("."));

    return {std::stoi(current), std::stoi(total)};
}

bool checkState(int t, std::vector<disc>& input) {
    for(int i = 0; i < input.size(); i++) {
        const disc& d{input.at(i)};
        if((t + i + 1 + d.currentPosition) % d.totalPositions != 0) {
            return false;
        }
    }

    return true;
}