#include "Day20.h"

int main() {
    std::vector<Range> ranges{};
    getLines<Range>(ranges, 2016, 20, string2range);

    long long out = 0;
    long long i = 0;
    while(i <= 4294967295) {
        long long result = inRanges(ranges, i);
        if(result == i) {
            if(out == 0) {
                print() << i << std::endl;
            }
            out++;
        } else {
            i = result;
        }

        i++;
    }

    print() << out;

    return 0;
}

Range string2range(const std::string& line) {
    auto pos{ line.find('-') };

    long long lower = std::stoll(line.substr(0, pos));
    long long higher = std::stoll(line.substr(pos + 1));

    return {lower, higher};
}

long long inRanges(const std::vector<Range>& ranges, long long x) {
    for(const Range& r: ranges) {
        if(r.inRange(x)) {
            return r.higher;
        }
    }
    return x;
}