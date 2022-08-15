#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>
#include <chrono> 

using clock_type = std::chrono::steady_clock;
using second_type = std::chrono::duration<double, std::ratio<1> >;

template<typename T>
using Parser = T(*)(const std::string&);

std::string& trim(std::string& str);

std::string getFileName(int year, int day);

std::string getFile(int year, int day);

void getLines(std::vector<std::string>& list, int year, int day);

template<typename T>
void getLines(std::vector<T>& list, int year, int day, Parser<T> parser) {
    std::vector<std::string> rawInput{};
    getLines(rawInput, year, day);
    for(std::string& s: rawInput) {
        list.push_back(parser(s));
    }
}

void getParagraphs(std::vector<std::string>& list, int year, int day);

template<typename T>
void getParagraphs(std::vector<T>& list, int year, int day, Parser<T> parser) {
    std::vector<std::string> rawInput{};
    getParagraphs(rawInput, year, day);
    for(std::string& s: rawInput) {
        list.push_back(parser(s));
    }
}

std::ostream& print(int part = 0);

#endif