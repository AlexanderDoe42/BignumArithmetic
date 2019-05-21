#include <iostream>

#include "number.h"

main() {
    Number n1;
    n1.print();
    std::string str;
    getline(std::cin, str);
    Number n2(str);
    n2.print();
}
