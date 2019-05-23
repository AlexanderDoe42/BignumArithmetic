#include <iostream>

#include "number.h"

short Number::char_to_short(char c) {
    return c-'0';
}

Number::Number() {
    length = 1;
    num = new short[1];
    num[0] = 0;
}

Number::Number(std::string& num_str) {
    length = num_str.length();
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = char_to_short(num_str[i]);
}

void Number::print() {
    for (int i = 0; i < length; i++)
        std::cout << num[i];
    std::cout << std::endl;
}

Number Number::operator+ (const Number& arg) {
    Number result;
    return result;
}

Number& Number::operator= (const Number& arg) {
    delete[] num;
    length = arg.length;
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = arg.num[i];
    return *this;
}

Number::~Number() {
    delete[] num;
}
