#include <iostream>
#include <string>

#include "../../../xpres.hpp"
#include "../../../matrix.hpp"

int main () {
    Xpres a = "t"_exp;
    Xpres b = "r + 1"_exp;
    std::cout << (b ^ a) << std::endl;
    
    a = "q + q"_exp;
    b = "r + 1"_exp;
    std::cout << (b - a) << std::endl;
    
    Xpres::iterator(a)[1] * "x"_exp;
    std::cout << a << std::endl;
    
    Xpres::iterator(a)[1] * "x"_exp;
    std::cout << a << std::endl;
    
    Xpres::iterator(a)[0] ^ "2"_exp;
    std::cout << a << std::endl;
    
    Xpres::iterator(a) ^ "2+r"_exp;
    std::cout << a << std::endl;
    
    return 0;
}
