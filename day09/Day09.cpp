#include "Day09.h"

int main() {
    std::string input{ getFile(2016, 9) };
    print() << decompress(input, false) << std::endl;;
    print() << decompress(input, true) << std::endl ;

    return 0;
}

size_t decompress(const std::string& compressed, bool part2) {
    size_t out{};
    
    bool inBuffer{false};
    std::string buffer{};

    for(int i = 0; i < compressed.size(); i++) {
        char c = compressed.at(i);

        if(c == '(') {
            inBuffer = true;
            continue;
        }

        if(c == ')') {
            inBuffer = false;

            int charCount{std::stoi(buffer.substr(0, buffer.find("x")))};
            int duplicateCount{std::stoi(buffer.substr(buffer.find("x")+1))};

            std::string toDuplicate{compressed.substr(i + 1, charCount)};
            size_t charCountInDuplication{part2? decompress(toDuplicate, true): toDuplicate.size()};
            out += duplicateCount * charCountInDuplication;
            i += charCount;

            buffer = {};
            continue;
        }

        if(inBuffer) buffer.append(std::string{c});
        else out++;
    }

    return out;
}