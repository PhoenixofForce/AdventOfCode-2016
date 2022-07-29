#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <string_view>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <regex>

std::string& trim(std::string& str);

std::string getFileName(int year, int day);

std::string getFile(int year, int day);

void getLines(std::vector<std::string>& list, int year, int day);

template<typename T>
void getLines(std::vector<T>& list, int year, int day, T parser(const std::string&));

void getParagraphs(std::vector<std::string>& list, int year, int day);

template<typename T>
void getParagraphs(std::vector<T>& list, int year, int day, T parser(const std::string&));

#endif