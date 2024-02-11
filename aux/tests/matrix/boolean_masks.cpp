#include <iostream>
#include <ranges>
#include <vector>
#include <cstdint>
#include <string>

void printm (uint64_t a) {
    uint64_t one = 1;
    std::cout << std::endl;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            std::cout << !!(a & (one << ((i << 3) + j))) << " ";
        }
        std::cout << std::endl;
    }
}

int main () {
    std::cout << "traspose masks" << std::endl;
    std::vector<int> vec = {
        56, 48, 40, 32, 24, 16, 8, 1, 2, 3, 4, 5, 6, 7
    };
    std::vector<int> ind = {
        1, 2, 3, 4, 5, 6, 7, 7, 6, 5, 4, 3, 2, 1
    };
    uint64_t res, one = 1;
    for (const auto & [a, b]: std::views::zip (vec, ind)) {
        res = 0;
        for (int i = 0; i < b; i++) {
            res |= one << (a + i*9);
        }
        std::cout << std::to_string(res) << "ULL, "; 
    }
    std::cout << std::endl;
    
    std::cout << std::endl << "row masks" << std::endl;
    std::vector<uint64_t> vec2;
    vec2.clear ();
    res = 255;
    for (int i = 0; i < 8; i++) {
        vec2.push_back (res);
        std::cout << std::to_string(res) << "ULL, ";
        res <<= 8;
    }
    
    std::cout << std::endl << "column masks" << std::endl;
    res = 0;
    res = one | (one << 8) | (one << 16) | (one << 24) | (one << 32) | (one << 40) | (one << 48) | (one << 56);
    for (int i = 0; i < 8; i++) {
        std::cout << res << "ULL, ";
        res <<= 1;
    }

    std::vector<uint64_t> vec1;
    vec1.clear ();
    std::cout << std::endl << "logarithm masks" << std::endl;
    vec1.push_back (vec2[7] | vec2[6] | vec2[5] | vec2[4]);
    vec1.push_back (vec2[3] | vec2[2]);
    vec1.push_back (vec2[1]);
    std::cout << vec1[0] << "ULL, ";
    std::cout << vec1[1] << "ULL, ";
    std::cout << vec1[2] << "ULL, ";

    printm(vec1[0]);
    printm(vec1[1]);
    printm(vec1[2]);

    std::cout << std::endl;

    return 0;
}
