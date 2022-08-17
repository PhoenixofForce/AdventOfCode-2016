#ifndef DAY21_H
#define DAY21_H

#include "../Utils.h"
#include <iostream>

struct Instruction {
    int functionType{};
    int firstArg{};
    int secondArg{};
    void(*function)(std::string&, int, int);
};

Instruction string2instruction(const std::string& instr, const std::string& input);

void swap(std::string& line, int pos1, int pos2);
/**
 * @param amount negative for right rotate, positive for left
 */
void rotate(std::string& line, int amount, int placeholder);
void reverse(std::string& line, int from, int to);
void move(std::string& line, int from, int to);


#endif