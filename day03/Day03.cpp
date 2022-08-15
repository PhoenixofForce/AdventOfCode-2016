#include "Day03.h"

int main() {
    std::vector<std::string> triangleLines{};
    getLines(triangleLines, 2016, 3);
    std::vector<Triangle> triangles{};
    for(std::string& line: triangleLines) triangles.push_back(line2Triangle(line));

    int out1{0};
    for(const Triangle& t: triangles) {
        if(checkTriangle(t)) out1++;
    }
    print() << out1 << std::endl;

    int out2{0};
    for(int i = 0; i < triangles.size(); i+=3) {
        Triangle& t1 = triangles.at(i + 0);
        Triangle& t2 = triangles.at(i + 1);
        Triangle& t3 = triangles.at(i + 2);

        Triangle n1 = {t1.a, t2.a, t3.a};
        Triangle n2 = {t1.b, t2.b, t3.b};
        Triangle n3 = {t1.c, t2.c, t3.c};

        if(checkTriangle(n1)) out2++;
        if(checkTriangle(n2)) out2++;
        if(checkTriangle(n3)) out2++;
    }
    print() << out2 << std::endl;

    return 0;
}

Triangle line2Triangle(const std::string& lineIn) {
    std::string line{lineIn + " "};
    std::vector<int> sides{};

    size_t pos;
    while((pos = line.find(" ")) != std::string::npos) {
        std::string side{ line.substr(0, pos) };
        if(side.length() <= 0) break;

        sides.push_back(std::stoi(side));

        line.erase(0, pos + 1);
    }

    return {sides.at(0), sides.at(1), sides.at(2)};
}

bool checkTriangle(const Triangle& triangle) {
    return triangle.a + triangle.b > triangle.c &&
           triangle.a + triangle.c > triangle.b &&
           triangle.c + triangle.b > triangle.a;
}