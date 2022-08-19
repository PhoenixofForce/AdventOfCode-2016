#include "Day21.h"

int main() {
    std::vector<std::string> instructions{};
    getLines(instructions, 2016, 21);

    std::string input{ "abcdefgh" };
    for(const std::string& line: instructions) {
        Instruction instr{ string2instruction(line, input) };
        instr.function(input, instr.firstArg, instr.secondArg);
    }
    print() << input << std::endl;

    int reverseRotate[10]{0, 1, 1, -2, 2, 0, -1, 3, 0, -4};

    input = "fbgdceah";
    std::reverse(instructions.begin(), instructions.end());
    for(const std::string& line: instructions) {
        Instruction instr{ string2instruction(line, input) };
        int firstArg = instr.functionType == 4? instr.secondArg: instr.firstArg;
        int secondArg = instr.functionType == 4? instr.firstArg: instr.secondArg;
        
        if(instr.functionType == 1) firstArg *= -1;
        if(instr.functionType == 2) {
            firstArg = reverseRotate[std::abs(firstArg)];
        }
        
        instr.function(input, firstArg, secondArg);
    }
    print() << input << std::endl;

    return 0;
}

Instruction string2instruction(const std::string& instr, const std::string& input) {
    if(instr.find("swap pos") == 0) {
        auto firstStart{ instr.find("p position") + 11 };
        auto secondStart{ instr.find("with position")  };

        int first = std::stoi(instr.substr(firstStart, secondStart - 1));
        secondStart += + 14;
        int second = std::stoi(instr.substr(secondStart));

        return {0, first, second, swap};
    }

    else if(instr.find("swap lett") == 0) {
        char firstChar = instr.at(12);
        char secondChar = instr.at(26);

        auto firstPos{ input.find(std::string{firstChar}) };
        auto secondPos{ input.find(std::string{secondChar}) };

        return {0, firstPos, secondPos, swap};
    }

    else if(instr.find("rotate left") == 0) {
        auto start{ instr.find("left") + 5 };
        int amount = std::stoi(instr.substr(start, instr.find("steps") - 1));

        return {1, amount, 0, rotate};
    }

    else if(instr.find("rotate right") == 0) {
        auto start{ instr.find("right") + 6 };
        int amount = std::stoi(instr.substr(start, instr.find("steps") - 1));

        return {1,-amount, 0, rotate};
    }

    else if(instr.find("rotate based") == 0) {
        char c = instr.at(instr.size() - 1);
        auto pos{ input.find(std::string{c}) };
        int amount = 1 + pos;
        if(pos >= 4) amount++;

        return {2, -amount, 0, rotate};
    }

    else if(instr.find("reverse") == 0) {
        auto fromStart{ instr.find("positions") + 10 };
        auto toStart{ instr.find("through") };

        int from = std::stoi(instr.substr(fromStart, toStart - 1));
        toStart += 8;
        int to = std::stoi(instr.substr(toStart));

        return {3, from, to, reverse};
    }

    else if(instr.find("move") == 0) {
        int first = std::stoi(std::string{instr.at(14)});
        int second = std::stoi(std::string{instr.at(instr.size() - 1)});

        return {4, first, second, move};
    }
}


void swap(std::string& line, int pos1, int pos2) {
    std::swap(line.at(pos1), line.at(pos2));
}

void rotate(std::string& line, int amount, int placeholder) {
    std::string newString{};
    for(int i = 0; i < line.size(); i++) {
        int otherPos = i + amount;
        while(otherPos < 0) otherPos += line.size();
        otherPos %= line.size();

        newString += line.at(otherPos);
    }
    line = newString;
}

void move(std::string& line, int from, int to) {
    char c = line.at(from);
    line.erase(line.begin() + from);
    line = line.substr(0, to) + c + line.substr(to);
}

void reverse(std::string& line, int from, int to) {
    std::reverse(line.begin() + from, line.begin() + to + 1);
}