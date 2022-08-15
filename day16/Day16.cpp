#include "Day16.h"

int main() {
    bool part2 = true;
    
    std::string input{ getFile(2016, 16) };
    int maxLength = part2? 35651584: 272;

    while(input.size() < maxLength) input = buildDragonCurve(input);
    print(part2? 2: 1) << generateChecksum(input, maxLength);

    return 0;
}

std::string buildDragonCurve(const std::string& line) {
    std::string secondPart{line};
    std::reverse(secondPart.begin(), secondPart.end());
    std::replace(secondPart.begin(), secondPart.end(), '1', '2');
    std::replace(secondPart.begin(), secondPart.end(), '0', '1');
    std::replace(secondPart.begin(), secondPart.end(), '2', '0');

    return line + "0" + secondPart;
}

std::string generateChecksum(const std::string& line, int maxLength) {
    std::string out{};
    for(int i{0}; i < std::min(maxLength, (int) line.size()); i += 2) {
        char c1 = line.at(i);
        char c2 = line.at(i + 1);
        out += (c1 == c2? "1": "0");
    }
    return out.size() % 2 == 0? generateChecksum(out, maxLength): out;
}