#include "Day07.h"

int main() {
    std::vector<std::string> lines{};
    getLines(lines, 2016, 07);
    
    int out{0};
    int out2{0};
    for(int i = 0; i < lines.size(); i++) {
        if(processLine(lines.at(i))) out++;
        if(processLine2(lines.at(i))) out2++;
    }
    print() << out << std::endl;
    print() << out2 << std::endl;

    return 0;
}

bool processLine(const std::string& line) {
    bool inBrackets = false;
    std::vector<char> buffer{};

    bool out = false;

    for(int i = 0; i < line.size(); i++) {
        char c = line.at(i);

        if(c == '[') {
            inBrackets = true;
            buffer.clear();
            continue;
        } else if(c == ']') {
            inBrackets = false;
            buffer.clear();
            continue;
        }

        buffer.push_back(c);
        if(buffer.size() > 4) buffer.erase(buffer.begin());

        if(buffer.size() == 4 && buffer.at(0) == buffer.at(3) && 
            buffer.at(0) != buffer.at(1) && buffer.at(1) == buffer.at(2)) {
            
            if(inBrackets) return false;
            else out = true;
        }
    }
    
    return out;
}

bool processLine2(const std::string& line) {
    bool inBrackets = false;
    std::vector<char> buffer{};

    std::vector<std::string> abas{};
    std::vector<std::string> babs{};

    for(int i = 0; i < line.size(); i++) {
        char c = line.at(i);

        if(c == '[') {
            inBrackets = true;
            buffer.clear();
            continue;
        } else if(c == ']') {
            inBrackets = false;
            buffer.clear();
            continue;
        }

        buffer.push_back(c);
        if(buffer.size() > 3) buffer.erase(buffer.begin());

        if(buffer.size() == 3 && buffer.at(0) == buffer.at(2) && 
            buffer.at(0) != buffer.at(1)) {
            (inBrackets? babs: abas).push_back( std::string{buffer.at(0)} + std::string{buffer.at(1)} + std::string{buffer.at(2)} );
        }
    }
    
    for(std::string& aba: abas) {
        for(std::string& bab: babs) {
            if(aba.at(0) == bab.at(1) && aba.at(1) == bab.at(0)) return true;
        }
    }

    return false;
}