#include "Day23.h"

int main() {
    bool part2{true};

    std::vector<std::string> input{};
    getLines(input, 2016, 23);

    std::map<std::string, int> registry{};
    int linePointer = 0;

    registry["a"] = (part2? 12: 7);

    std::vector<std::string> splitted{};
    while(linePointer >= 0 && linePointer < input.size()) {
        std::string& line{ input.at(linePointer) };
        
        std::vector<std::string> lineArgs{};
        split(lineArgs, line, " ");

        if(lineArgs.at(0).find("cpy") == 0) {
            int value = toValue(registry, lineArgs.at(1));

            std::string& registryName{ lineArgs.at(2) };
            registry[registryName] = value;
        }

        else if(lineArgs.at(0).find("inc") == 0) {
            std::string& registryName{ lineArgs.at(1) };
            registry[registryName] = toValue(registry, registryName) + 1;
        }

        else if(lineArgs.at(0).find("dec") == 0) {
            std::string& registryName{ lineArgs.at(1) };
            registry[registryName] = toValue(registry, registryName) - 1;
        }

        else if(lineArgs.at(0).find("jnz") == 0) {
            std::string& registryName{ lineArgs.at(1) };
            int value = toValue(registry, lineArgs.at(2));

            if(toValue(registry, registryName) != 0) {
                if(value == -5 && linePointer == 9) {   //this part might work just for my input.
                    registry["a"] += registry["b"] * registry["d"];
                    registry["d"] = 0;
                } else {
                    linePointer += value-1;
                }
            } 
        }

        else if(lineArgs.at(0).find("tgl") == 0) {
            std::string& registryName{ lineArgs.at(1) };
            int value = toValue(registry, registryName);
            
            if(linePointer + value < input.size()) {
                std::string& toChange{ input.at(linePointer + value) };
                toChange = std::regex_replace(toChange, std::regex{"inc"}, "plc");
                toChange = std::regex_replace(toChange, std::regex{"dec"}, "inc");
                toChange = std::regex_replace(toChange, std::regex{"plc"}, "dec");
                toChange = std::regex_replace(toChange, std::regex{"tgl"}, "inc");

                toChange = std::regex_replace(toChange, std::regex{"jnz"}, "plc");
                toChange = std::regex_replace(toChange, std::regex{"cpy"}, "jnz");
                toChange = std::regex_replace(toChange, std::regex{"plc"}, "cpy");
            }
        }

        linePointer++;
    }

    print(part2? 2: 1) << registry["a"];

    return 0;
}

void split(std::vector<std::string>& list, const std::string& toSplit, const std::string& delim, bool filterEmpty) {
    int pos = 0;
    while(toSplit.find(delim, pos) != std::string::npos) {
        int newPos = toSplit.find(delim, pos);
        std::string toPush = toSplit.substr(pos, newPos - pos);
        if(!filterEmpty || toPush.size() > 0) list.push_back(toPush);
        pos = newPos + delim.size();
    }
    if(pos < toSplit.size()) {
        std::string toPush = toSplit.substr(pos);
        if(!filterEmpty || toPush.size() > 0) list.push_back(toPush);
    }
}

int toValue(const std::map<std::string, int>& registry, const std::string& valueName) {
     if(valueName.at(0) >= 'a' && valueName.at(0) <= 'z') {
        return (registry.find(valueName) != registry.end()? registry.at(valueName): 0); 
    } else {
        return std::stoi(valueName);
    }
}