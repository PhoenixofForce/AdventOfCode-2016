#include "Day04.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 04);

    int out = 0;
    for(std::string line: input) {
        out += sectorId(line);
    }
    print(1) << out << std::endl;

    return 0;
}

int sectorId(const std::string& line) {
    std::vector<Letter> letters{};
    std::string sector{};
    std::string checksum{};

    std::string name{};

    bool isChecksum = false;
    for(int i = 0; i < line.size(); i++) {
        char c = line.at(i);
        
        if(c == '-' || c== ']') continue;
        if(c == '[') {
            isChecksum = true;
            continue;
        }

        if(isChecksum) {
            checksum += c;
            continue;
        }

        if('0' <= c && c <= '9') {
            sector += c;
            continue;
        }

        if(!isChecksum) {
            name += c;
        }

        auto pos = std::find_if(letters.begin(), letters.end(), [c](const Letter& l) -> bool {
            return l.c == c;
        });

        if(pos != letters.end()) {
            letters.at(std::distance(letters.begin(), pos)).count++;
        } else {
            letters.push_back({c, 1});
        }
    }

    bool isValid = true;
    std::sort(letters.begin(), letters.end(), [](const Letter& a, const Letter& b) -> bool {
        if(a.count == b.count) return a.c < b.c;
        else return a.count > b.count;
    });

    for(int i = 0; i < 5; i++) {
        if(letters.at(i).c != checksum.at(i)) isValid = false;
    } 

    if(isValid) {
        std::string decr = decrypt(name, std::stoi(sector));
        if(decr.find("north") != std::string::npos) {
            print(2) << decr << " " << sector << std::endl;
        }
    }

    return isValid? std::stoi(sector): 0;
}

std::string decrypt(const std::string& line, int sectorId) {
    std::string out{};
    for(int i = 0; i < line.size(); i++) {
        out += ((line.at(i) - 'a' + sectorId) % 26) + 'a';
    }
    return out;
}