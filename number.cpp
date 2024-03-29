 #include <iostream>
 #include <string>

 #include "number.h"

short Number::char_to_short(char c)
{
    return c-'0';
}

Number Number::addition(const Number& arg)
{
    Number result;
    result.length = (length > arg.length) ? length+1 : arg.length+1;
    for (List<short>::iterator it = num.begin(); it != num.end(); it++)
        result.num.add(*it);
    while (result.num.size() != result.length)
        result.num.add_front(0);

    List<short>::iterator it_result_num = result.num.last();
    List<short>::iterator it_arg_num = arg.num.last();
    short tmp = 0;
    for (int i = 0; i < arg.length; i++) {
        short sum = *it_result_num + *it_arg_num + tmp;
        *it_result_num = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
        it_result_num--;
        it_arg_num--;
    }

    for (int i = arg.length; i < result.length && tmp == 1; i++) {
        short sum = *it_result_num + tmp;
        *it_result_num = sum % 10;
        tmp = (sum > 9) ? 1 : 0;
        it_result_num--;
        it_arg_num--;
    }

    if (*result.num.begin() == 0) {
        --result.length;
        result.num.remove(result.num.begin());
    }

    return result;
}

Number Number::subtraction(const Number& arg1, const Number& arg2)
{
    Number result;
    short tmp = 0;
    List<short>::iterator it_arg1_num = arg1.num.last();
    List<short>::iterator it_arg2_num = arg2.num.last();
    int i = 0;
    while (it_arg2_num != arg2.num.end()) {
        if (*it_arg1_num >= *it_arg2_num + tmp) {
            result.num.add_front(*it_arg1_num - *it_arg2_num - tmp);
            tmp = 0;
        } else {
            result.num.add_front(10 + *it_arg1_num - *it_arg2_num - tmp);
            tmp = 1;
        }
        it_arg1_num--;
        it_arg2_num--;
    }
    while (it_arg1_num != arg1.num.end() && tmp == 1) {
        if (*it_arg1_num >= tmp) {
            result.num.add_front(*it_arg1_num - tmp);
            tmp = 0;
        } else {
            result.num.add_front(10 + *it_arg1_num - tmp);
            tmp = 1;
        }
        it_arg1_num--;
    }
    while (it_arg1_num != arg1.num.end()) {
        result.num.add_front(*it_arg1_num);
        it_arg1_num--;
    }

    List<short>::iterator it = result.num.begin();
    while (*it == 0) {
        result.num.remove(it);
        it++;
    }

    result.length = result.num.size();

    return result;
}

Number Number::halfOf(const Number& arg)
{
    if (arg == Number("0") || arg == Number("1"))
        return Number("0");

    Number result;

    short tmp = 0;
    for (List<short>::iterator it = arg.num.begin(); it != arg.num.end(); it++) {
        result.num.add( (tmp + *it) / 2 );
        tmp = (*it % 2) * 10;
    }

    if (*result.num.begin() == 0)
        result.num.remove(result.num.begin());

    result.length = result.num.size();

    return result;
}

Number Number::abs(const Number & arg)
{
    Number result = arg;
    result.negativeNum = false;
    return result;
}

Number::Number()
{
    negativeNum = false;
    length = 0;
}

Number::Number(std::string& num_str)
{
    if (num_str[0] == '-') {
        negativeNum = true;
        length = num_str.length() - 1;
        for (int i = 0; i < length; i++)
            num.add (char_to_short (num_str[i+1]) );
    } else {
        negativeNum = false;
        length = num_str.length();
        for (int i = 0; i < length; i++)
            num.add (char_to_short (num_str[i]) );
    }
    if (length == 1 && *num.begin() == 0)
        negativeNum = false;
}

Number::Number(const char * num_str)
{
    if (num_str[0] == '-') {
        negativeNum = true;
        for (int i = 1; num_str[i] != '\0'; i++)
            num.add( char_to_short(num_str[i]) );
    } else {
        negativeNum = false;
        for (int i = 0; num_str[i] != '\0'; i++)
            num.add( char_to_short(num_str[i]) );
    }
    length = num.size();
    if (length == 1 && *num.begin() == 0)
        negativeNum = false;
}

Number::Number(const Number& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    for (List<short>::iterator it = arg.num.begin(); it != arg.num.end(); it++)
        num.add(*it);
}

Number::Number(Number&& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = arg.num;
}

void Number::print()
{
    if (negativeNum)
        std::cout << '-';
    for (List<short>::iterator it = num.begin(); it != num.end(); it++)
        std::cout << *it;
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
            return Number("0");
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
        return Number("0");

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

// Number Number::operator* (const Number& arg)
// {
//     if (*this == Number("0") || arg == Number("0"))
//         return Number("0");
//
//     int newlen = length + arg.length;
//     List<short> newnum;
//
//     for (int i = 0; i < newlen; i++)
//         newnum.add(0);
//
//     List<short>::iterator it_newnum = newnum.last();
//     for (List<short>::iterator it_arg_num = arg.num.last(); it_arg_num != arg.num.end(); it_arg_num--) {
//         int tmp = 0;
//         List<short>::iterator it_newnum2 = it_newnum;
//         for (List<short>::iterator it_num = num.last(); it_num != num.end(); it_num--) {
//             short sum = *it_newnum2 + *it_num * *it_arg_num + tmp;
//             *it_newnum2 = sum % 10;
//             tmp = sum / 10;
//             it_newnum2--;
//         }
//         *it_newnum2 = tmp;
//         it_newnum--;
//     }
//
//     if (*newnum.begin() == 0) {
//         --newlen;
//         newnum.remove(newnum.begin());
//     }
//     Number result;
//     result.num.moveAssignment(newnum);
//     result.length = newlen;
//
//     if ((negativeNum && !arg.negativeNum) || (!negativeNum && arg.negativeNum))
//         result.negativeNum = true;
//
//     return result;
// }

Number Number::basicMult(const Number& x, const Number& y) { //the lenth of y has to be 1
  if (x == Number("0") || y == Number("0")) {
    return Number("0");
  }
  Number result;
  int tmp = 0;
  for (List<short>::iterator it = x.num.last(); it != x.num.end(); it--) {
    int p = *it * *y.num.begin() + tmp;
    result.num.add_front(p % 10);
    tmp = p / 10;
  }
  if (tmp != 0) {
    result.num.add_front(tmp);
  }
  result.length = result.num.size();
  return result;
}

void Number::getLeftPart(Number& result, const Number& n, int divLen) {
  int size = n.length - divLen;
  List<short>::iterator it = n.num.begin();
  for (int i = 0; i < size; i++) {
    result.num.add(*it);
    it++;
  }
  result.length = result.num.size();
}

void Number::getRightPart(Number& result, const Number& n, int divLen) {
  List<short>::iterator it = n.num.last();
  for (int i = 0; i < divLen; i++) {
    result.num.add_front(*it);
    it--;
  }
  it = result.num.begin();
  while (*it == 0 && result.num.size() != 1) {
      result.num.remove(it);
      it++;
  }
  result.length = result.num.size();
}

void Number::addZeros(Number& n, int p) {
  for (int i = 0; i < p; i++) {
    n.num.add(0);
  }
  n.length = n.num.size();
}

Number Number::karatsMult(const Number& x,const Number& y) {
  if (x.length == 1) {
    return basicMult(y, x);
  }
  if (y.length == 1) {
    return basicMult(x, y);
  }

  int divLen = std::min(x.length, y.length) / 2;
  Number a;
  Number b;
  Number c;
  Number d;

  getLeftPart(a, x, divLen);
  getRightPart(b, x, divLen);
  getLeftPart(c, y, divLen);
  getRightPart(d, y, divLen);

  Number ac = karatsMult(a, c);
  Number bd = karatsMult(b, d);
  Number adbc = karatsMult(a+b, c+d) - bd - ac;

  addZeros(ac, divLen*2);
  addZeros(adbc, divLen);

  return ac + adbc + bd;
}

Number Number::operator* (const Number& arg)
{
    if (*this == Number("0") || arg == Number("0"))
        return Number("0");

    Number result = karatsMult(*this, arg);

    if ((negativeNum && !arg.negativeNum) || (!negativeNum && arg.negativeNum))
        result.negativeNum = true;

    return result;
}

Number Number::operator/ (const Number & arg)
{
    if (arg == Number("0")) {
        printf("Fatal error!");
        return arg;
    }

    if (*this == Number("0"))
        return Number("0");

    // ----dumb division---------------
    // Number result = *this;
    // while (*this < result * arg) {
    //     result--;
    // }
    //---------------------------------

    Number result = this->abs();

    Number minSearchBoundary("0");
    Number maxSearchBoundary = this->abs();

    Number this_abs = this->abs();
    Number arg_abs = arg.abs();

    while (abs(this_abs - result * arg_abs) >= arg_abs ) {
        if (result * arg_abs > this_abs) {
            maxSearchBoundary = result;
            result = result - halfOf(result - minSearchBoundary);
        } else if (result * arg_abs < this_abs) {
            minSearchBoundary = result;
            result = result + halfOf(maxSearchBoundary - result);
        }
    }

    if (result * arg_abs > this_abs)
        result--;

    if ((negativeNum && !arg.negativeNum) || (!negativeNum && arg.negativeNum))
        result.negativeNum = true;

    result.length = result.num.size();

    return result;
}

Number Number::operator++ (int)
{
    *this = *this + Number("1");
    return *this;
}

Number Number::operator-- (int)
{
    *this = *this - Number("1");
    return *this;
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
        List<short>::iterator it_num = num.begin();
        List<short>::iterator it_arg_num = arg.num.begin();
        while (it_num != num.end()) {
            if (*it_num > *it_arg_num) {
                result = true;
                break;
            }
            if (*it_num < *it_arg_num) {
                result = false;
                break;
            }
            it_num++;
            it_arg_num++;
        }
    }

    if (negativeNum && arg.negativeNum)
        result = !result;

    return result;
}

bool Number::operator< (const Number& arg)
{
    if (*this > arg || *this == arg)
        return false;
    return true;
}

bool Number::operator>= (const Number& arg)
{
    if (*this == arg || *this > arg)
        return true;
    return false;
}

bool Number::operator== (const Number& arg) const
{
    if ( (length != arg.length) || (negativeNum && !arg.negativeNum) ||
         (!negativeNum && arg.negativeNum) )
        return false;

    List<short>::iterator it_num = num.begin();
    List<short>::iterator it_arg_num = arg.num.begin();
    while (it_num != num.end()) {
        if (*it_num != *it_arg_num)
            return false;
        it_num++;
        it_arg_num++;
    }

    return true;
}

bool Number::operator!= (const Number& arg) const
{
    if (*this == arg)
        return false;
    return true;
}

Number& Number::operator= (const Number& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    num = arg.num;
    return *this;
}

Number& Number::operator= (Number&& arg)
{
    negativeNum = arg.negativeNum;
    length = arg.length;
    num.moveAssignment(arg.num);
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
}
