#include <iostream>
#include "longNum.h"


int main() {
    std::string s1, s2;
    std::cin >> s1 >> s2;
    num::longNum n1(s1), n2(s2);
    std::cout << n1 << '+' << n2 << '=' << n1 + n2 << std::endl;
    std::cout << n1 << '-' << n2 << '=' << n1 - n2 << std::endl;
    std::cout << n1 << '*' << n2 << '=' << n1 * n2 << std::endl;
    std::cout << n1 << '/' << n2 << '=' << n1 / n2 << std::endl;
    std::cout << n1 << '%' << n2 << '=' << n1 % n2 << std::endl;
    return 0;
}
