#ifndef DAY20_H
#define DAY20_H

#include "../Utils.h"
#include <iostream>

struct Range {
    long long lower{};
    long long higher{};

    bool inRange(long long x) const {
        return x >= lower && x <= higher;
    }
};

Range string2range(const std::string& line);
long long inRanges(const std::vector<Range>& ranges, long long x);

#endif