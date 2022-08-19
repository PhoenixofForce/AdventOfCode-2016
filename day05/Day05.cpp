#include "Day05.h"

int main() {
    std::string input{ getFile(2016, 05) };
    std::cout << "Loaded Input: " << input << std::endl;
    std::string out{};

    int index = 0;
    while(out.size() < 8) {
        std::string hash{ md5(input + std::to_string(index)) };

        if(hash.find("00000") == 0) {
            out += hash.at(5);
            std::cout << "Found " << out.size() << ". digit: " << hash.at(5) << " by hashing " << input << index << " which is " << hash << std:: endl;
        }

        index++;
    }
    print() << out << std::endl;

    char out2[8]{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
    int found = 0;
    index = 0;

    while(found < 8) {
         std::string hash{ md5(input + std::to_string(index)) };

        if(hash.find("00000") == 0) {
            char cIndex = hash.at(5);
            char character = hash.at(6);

            if(cIndex >= '0' && cIndex <= '7') {
                int iIndex = std::stoi(std::string{cIndex});
                if(out2[iIndex] == ' ') {
                    out2[iIndex] = character;
                    found++;

                    std::cout << "Found " << iIndex << ". digit: " << character << " by hashing " << input << index << " which is " << hash << std:: endl;
                }
            }
        }

        index++;
    }

    print();
    for(int i = 0; i < 8; i++) {
        std::cout << out2[i];
    }
    std::cout << std::endl;

    return 0;
}