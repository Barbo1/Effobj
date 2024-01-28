#include <utility>
#include <iostream>
#include <any>

int main () {
    unsigned a = 2;
    float b = 0.5;
    std::pair<std::any, std::any> c = std::pair<std::any, std::any>(a, b);
    std::cout << (c.first + c.second) << std::endl;
    return 0;
}
