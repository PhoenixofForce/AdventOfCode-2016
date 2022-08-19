#include "Day10.h"

int main() {
    std::vector<std::string> input{};
    getLines(input, 2016, 10);

    std::map<int, Robot> bots{};
    std::map<int, std::vector<int>> outputs;

    //parse input
    for(std::string& line: input) {
        if(line.find("value") == 0) {
            int value = std::stoi(line.substr(6, line.find("goes") - 7));
            int botID = std::stoi(line.substr(line.find("bot") + 4));
            
            if(bots.find(botID) == bots.end()) {
                bots[botID] = Robot{botID};
            }

            Robot* bot{findBot(bots, botID)};
            bot->chips.push_back(value);
        }

        else if(line.find("bot") == 0) {
            int botID = std::stoi(line.substr(4, line.find("gives") - 5));

            if(bots.find(botID) == bots.end()) {
                bots[botID] = Robot{botID};
            }

            Robot* bot{findBot(bots, botID)};
            bot->instruction = (parseInstructions(line));
        }
    }

    //run simulation
    bool change = true;
    while(change) {
        change = false;

        for(auto&[id, bot]: bots) {
            if(bot.chips.size() == 2) {
                change = true;

                int lower = bot.chips.at(0);
                int higher = bot.chips.at(1);
                bot.chips.clear();
                if(lower > higher) std::swap(lower, higher);

                //Part1
                if(lower == 17 && higher == 61) {
                    print() << bot.id << std::endl;
                }

                const InstructionResolve& instr{ bot.instruction };

                //move lower chip to bot
                if(instr.lowerID >= 0) {
                    if(bots.find(instr.lowerID) == bots.end()) {
                        bots[instr.lowerID] = Robot{instr.lowerID};
                    }
                    Robot* bot{ findBot(bots, instr.lowerID) };
                    bot->chips.push_back(lower);
                } 
                
                //move lower chip to output
                else {
                    int outputID = -(instr.lowerID + 1);
                    if(outputs.find(outputID) == outputs.end()) {
                        outputs[outputID] = std::vector<int>{};
                    }
                    outputs[outputID].push_back(lower);
                }

                //move higher chip to bot
                if(instr.higherID >= 0) {
                    if(bots.find(instr.higherID) == bots.end()) {
                        bots[instr.higherID] = Robot{instr.higherID};
                    }
                    Robot* bot{ findBot(bots, instr.higherID) };
                    bot->chips.push_back(higher);
                } 
                
                //move higher chip to output
                else {
                    int outputID = -(instr.higherID + 1);
                    if(outputs.find(outputID) == outputs.end()) {
                        outputs[outputID] = std::vector<int>{};
                    }
                    outputs[outputID].push_back(higher);
                }

                break;
            }
        }
    }

    long out = 1;
    for(int i = 0; i <= 2; i++) {
        std::vector<int>& outputI = outputs[i];
        for(int i: outputI) {
            out *= i;
        }
    }
    print() << out;

    return 0;
}

InstructionResolve parseInstructions(const std::string& instruction) {
    int low = 0;
    int high = 0;

    if(instruction.find("low to bot") != std::string::npos) {
        size_t lowStart = instruction.find("low to bot") + 11;
        low = std::stoi(instruction.substr(lowStart, instruction.find("and high") - lowStart - 1));
    }

    if(instruction.find("low to output") != std::string::npos) {
        size_t lowStart = instruction.find("low to output") + 14;
        low = -std::stoi(instruction.substr(lowStart, instruction.find("and high") - lowStart - 1)) - 1;
    }

     if(instruction.find("high to bot") != std::string::npos) {
        size_t highStart = instruction.find("high to bot") + 12;
        high = std::stoi(instruction.substr(highStart));
    }

    if(instruction.find("high to output") != std::string::npos) {
        size_t highStart = instruction.find("high to output") + 15;
        high = -std::stoi(instruction.substr(highStart)) - 1;
    }

    return {low, high};
}

Robot* findBot(std::map<int, Robot>& bots, int id) {
    if(bots.find(id) != bots.end()) {
        return &bots[id];
    }
    return nullptr;
}