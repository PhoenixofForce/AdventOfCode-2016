#include "Day14.h"

int main() {
    std::string input{ getFile(2016, 14) };
    
    int i{0};
    int keysFound{0};
    while(keysFound < 64) {
        std::string currentKey{input + std::to_string(i)};
        std::string hashed{hash(currentKey)};

        std::smatch match{};
        if(std::regex_search(hashed, match, std::regex("(.)\\1{2}"))) {
            for(int j = 1; j <= 1000; j++) {
                std::string futureKey{input + std::to_string(i+j)};
                std::string futureHashed{hash(futureKey)};

                if(std::regex_search(futureHashed, std::regex("(" + match.str(1) + ")\\1{4}"))) {
                    keysFound++;
                    (keysFound == 64? print(): std::cout) << "Key " << keysFound << ", index: " << i << " = " << hashed << std::endl;   
                    break;
                }
            }
        }

        i++;
    }

    return 0;
}

std::string hash(const std::string& tohash) {
    static std::map<std::string, std::string> results{};
    if(results.find(tohash) != results.end()) return results[tohash];

    std::string outHash{tohash};
    for(int i = 0; i <= 2016; i++) {     //DELETE this for part 1
        outHash = md5(outHash);
    }
    results[tohash] = outHash;
    return outHash;
}