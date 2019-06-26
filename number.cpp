#include <iostream>

#include "number.h"

short Number::char_to_short(char c)
{
    return c-'0';
}

Number Number::addition(const Number& arg)
{
    int newlen = (length > arg.length) ? length+1 : arg.length+1;
    short * newnum = new short[newlen];
    for (int i = 0; i < length; i++)
        newnum[i] = num[i];

    short tmp = 0;
    for (int i = 0; i < arg.length; i++) {
        short sum = newnum[i] + arg.num[i] + tmp;
        newnum[i] = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
    }

    for (int i = arg.length; i < newlen && tmp == 1; i++) {
        short sum = newnum[i] + tmp;
        newnum[i] = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
    }

    Number result;
    delete[] result.num;
    if (newnum[newlen-1] == 0) {
        --newlen;
        result.num = new short[newlen];
        for (int i = 0; i < newlen; i++)
            result.num[i] = newnum[i];
        delete[] newnum;
    } else {
        result.num = newnum;
        newnum = NULL;
    }
    result.length = newlen;

    return result;
}

Number Number::subtraction(const Number& arg1, const Number& arg2)
{
    int newlen = arg1.length;
    short * newnum = new short[newlen];
    short tmp = 0;
    int i = 0;
    while (i < arg2.length) {
        if (arg1.num[i] >= arg2.num[i] + tmp) {
            newnum[i] = arg1.num[i] - arg2.num[i] - tmp;
            tmp = 0;
        } else {
            newnum[i] = 10+arg1.num[i] - arg2.num[i] - tmp;
            tmp = 1;
        }
        i++;
    }
    while (i < arg1.length && tmp == 1) {
        if (arg1.num[i] >= tmp) {
            newnum[i] = arg1.num[i] - tmp;
            tmp = 0;
        } else {
            newnum[i] = 10+arg1.num[i] - tmp;
            tmp = 1;
        }
        i++;
    }
    while (i < arg1.length) {
        newnum[i] = arg1.num[i];
        i++;
    }

    for (int i = newlen-1; i >= 0; i--) {
        if (newnum[i] != 0) {
            newlen = i+1;
            break;
        }
    }

    Number result;
    delete[] result.num;
    result.length = newlen;
    result.num = new short[newlen];
    for (int i = 0; i < newlen; i++)
        result.num[i] = newnum[i];
    delete[] newnum;

    return result;
}

Number::Number()
{
    negativeNum = false;
    length = 1;
    num = new short[1];
    num[0] = 0;
}

Number::Number(std::string& num_str)
{
    if (num_str[0] == '-') {
        negativeNum = true;
        length = num_str.length() - 1;
        num = new short[length];
        for (int i = 0; i < length; i++)
            num[i] = char_to_short(num_str[length-i]);
    } else {
        negativeNum = false;
        length = num_str.length();
        num = new short[length];
        for (int i = 0; i < length; i++)
            num[i] = char_to_short(num_str[length-1-i]);
    }
    if (length == 1 && num[0] == 0)
        negativeNum = false;
}

Number::Number(const Number& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = arg.num[i];
}

Number::Number(Number&& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = arg.num;
    arg.num = NULL;
}

void Number::print()
{
    if (negativeNum)
        std::cout << '-';
    for (int i = length-1; i >= 0; i--)
        std::cout << num[i];
    std::cout << std::endl;
}

Number Number::operator+ (const Number& arg)
{
    Number result;

    if ((negativeNum && arg.negativeNum) || (!negativeNum && !arg.negativeNum)) {
        result = addition(arg);
        if (negativeNum)
            result.negativeNum = true;
    } else {
        if (this->abs() == arg.abs())
            return Number();
        if (this->abs() > arg.abs()) {
            result = subtraction(*this, arg);
            if (negativeNum)
                result.negativeNum = true;
        } else {
            result = subtraction(arg, *this);
            if (!negativeNum)
                result.negativeNum = true;
        }
    }

    return result;
}

Number Number::operator- (const Number& arg)
{
    if (*this == arg)
        return Number();

    Number result;

    if ((negativeNum && arg.negativeNum) || (!negativeNum && !arg.negativeNum)) {
        if (this->abs() > arg.abs()) {
            result = subtraction(*this, arg);
            if (negativeNum)
                result.negativeNum = true;
        } else {
            result = subtraction(arg, *this);
            if (!negativeNum)
                result.negativeNum = true;
        }
    } else {
        result = addition(arg);
        if (negativeNum)
            result.negativeNum = true;
    }

    return result;
}

Number Number::operator* (const Number& arg)
{
    if (*this == Number() || arg == Number())
        return Number();

    int newlen = length + arg.length;
    short * newnum = new short[newlen];

    for (int j = 0; j < arg.length; j++) {
        int tmp = 0;
        for (int i = 0; i < length; i++) {
            short sum = newnum[i+j] + num[i] * arg.num[j] + tmp;
            newnum[i+j] = sum % 10;
            tmp = sum / 10;
        }
        newnum[length+j] = tmp;
    }

    Number result;
    delete[] result.num;
    if (newnum[newlen-1] == 0) {
        --newlen;
        result.num = new short[newlen];
        for (int i = 0; i < newlen; i++)
            result.num[i] = newnum[i];
        delete[] newnum;
    } else {
        result.num = newnum;
        newnum = NULL;
    }
    result.length = newlen;

    if ((negativeNum && !arg.negativeNum) || (!negativeNum && arg.negativeNum))
        result.negativeNum = true;

    return result;
}

bool Number::operator> (const Number& arg)
{
    if (*this == arg)
        return false;

    if (negativeNum && !arg.negativeNum)
        return false;

    if (!negativeNum && arg.negativeNum)
        return true;

    bool result = false;

    if (length > arg.length)
        result = true;

    if (length < arg.length)
        result = false;

    if (length == arg.length) {
        for (int i = length-1; i >= 0; i--) {
            if (num[i] > arg.num[i]) {
                result = true;
                break;
            }
            if (num[i] < arg.num[i]) {
                result = false;
                break;
            }
        }
    }

    if (negativeNum && arg.negativeNum)
        result = !result;

    return result;
}

bool Number::operator== (const Number& arg) const
{
    if ( (length != arg.length) || (negativeNum && !arg.negativeNum) ||
         (!negativeNum && arg.negativeNum) )
        return false;

    for (int i = 0; i < length; i++)
        if (num[i] != arg.num[i])
            return false;

    return true;
}

Number& Number::operator= (const Number& arg)
{
    delete[] num;
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = new short[length];
    for (int i = 0; i < length; i++)
        num[i] = arg.num[i];
    return *this;
}

Number& Number::operator= (Number&& arg)
{
    delete[] num;
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = arg.num;
    arg.num = NULL;
    return *this;
}

Number Number::abs() const
{
    Number result = *this;
    result.negativeNum = false;
    return result;
}

Number::~Number()
{
    delete[] num;
}
