#include "../../xpres.hpp"

Xpres operator""_exp(const char* exp, size_t) {
    return Xpres(std::string(exp));
}
