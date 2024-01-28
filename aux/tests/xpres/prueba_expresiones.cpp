#include "../xpres.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <utility>

int main() {
    unsigned i = 0;
    std::vector<std::pair<std::string, bool>> expresiones{
        std::pair<std::string, bool> {"!!!2", true},
        std::pair<std::string, bool> {"!!!+2", false},
        std::pair<std::string, bool> {"(1.211 - A*.34 + !12 + !(Ni))*4 ^ (1/7)", true},
        std::pair<std::string, bool> {"3 -1. - .23i", false},
        std::pair<std::string, bool> {"3 !-2 !-!i.23", false},
        std::pair<std::string, bool> {"3 -1. - i.23", false},
        std::pair<std::string, bool> {"q * TC(2 - !13) * ", false},
        std::pair<std::string, bool> {"TC(2 - !13)2", true},
        std::pair<std::string, bool> {"2 - !13)2", false},
        std::pair<std::string, bool> {"(2 - )", false},
        std::pair<std::string, bool> {"2 - !13!", false},
        std::pair<std::string, bool> {"q * TC(2 - !13)", true},
        std::pair<std::string, bool> {"3 -1-. - .23i", false},
        std::pair<std::string, bool> {"(^2)^!0", false},
        std::pair<std::string, bool> {"-(-((1)))", true},
        std::pair<std::string, bool> {"!--!-a", true},
        std::pair<std::string, bool> {".-.+.2", true},
        std::pair<std::string, bool> {"a!-0", false},
        std::pair<std::string, bool> {"(-!4*.3)*2^.", true},
        std::pair<std::string, bool> {"(-!4*.3)**2^.", false},
        std::pair<std::string, bool> {"(((1)))", true},
        std::pair<std::string, bool> {"(1..1)", false},
        std::pair<std::string, bool> {"(.-1.|.1)", true},
        std::pair<std::string, bool> {"(1.|.1))",false},
        std::pair<std::string, bool> {"(1.|.(1)",false},
        std::pair<std::string, bool> {"(1.|-|.1)", false},
        std::pair<std::string, bool> {"1 + cos(1 + 2)", true},
        std::pair<std::string, bool> {"1 + 1.3(1 + 2)", false},
        std::pair<std::string, bool> {"cos(a)", true}
    };

    for(auto it = expresiones.begin(); it != expresiones.end(); it++) {
        if (validate_string_expresion(it->first) != it->second) {
            std::cout << "error in " << it->first << std::endl;
            i++;
        }
    }
    if(i == 0) {
        std::cout << "all OK" << std::endl;
    }
}
