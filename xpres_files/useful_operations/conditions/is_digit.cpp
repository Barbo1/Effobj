#include "../../../xpres.hpp"

bool Xpres::is_digit (char let) {
  return std::isdigit(let) || let == '.';
}
