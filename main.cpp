#include <iostream>
#include <string>

#include "number.h"

main() {
    std::string str;

    while (true) {
        getline(std::cin, str);
        Number n1(str);

        getline(std::cin, str);
        Number n2(str);

        n1 = n1/n2;

        n1.print();
    }
}
