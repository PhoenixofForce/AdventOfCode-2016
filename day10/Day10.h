#ifndef DAY10_H
#define DAY10_H

#include "../Utils.h"
#include <iostream>
#include <optional>
#include <cmath>

struct InstructionResolve {
    int lowerID{};
    int higherID{};
};

struct Robot {
    int id{};
    std::vector<int> chips{};
    InstructionResolve instruction{};
};

InstructionResolve parseInstructions(const std::string& instruction);
Robot* findBot(std::map<int, Robot>& bots, int id);

#endif