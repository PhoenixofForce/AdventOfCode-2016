#include "Day19.h"

int main() {
    int numberOfElves = std::stoi(getFile(2016, 19));
    std::deque<Elve> elves{};

    for(int i = 0; i < numberOfElves; i++) {
        elves.push_back({i, 1});
    }

    int startElve = 0;
    while(elves.size() > 1) {
        Elve e = elves.front();
        elves.pop_front();
        elves.pop_front();
        elves.push_back(e);
    }
    print(1) << elves.front().id+1 << std::endl;;

    std::deque<Elve> elvesLeft{};
    std::deque<Elve> elvesRight{};

    for(int i = 0; i < numberOfElves; i++) {
        if(i <= numberOfElves / 2) elvesLeft.push_back({i, 1});
        else elvesRight.push_front({i, 1});
    }

    while(elvesLeft.size() > 0 && elvesRight.size() > 0) {
        if(elvesLeft.size() > elvesRight.size()) elvesLeft.pop_back();
        else elvesRight.pop_back();

        elvesRight.push_front(elvesLeft.front());
        elvesLeft.pop_front();
        elvesLeft.push_back(elvesRight.back());
        elvesRight.pop_back();
    }
    print() << (elvesLeft.size() > 0 ? elvesLeft.front().id+1: elvesRight.back().id+1);

    return 0;
}