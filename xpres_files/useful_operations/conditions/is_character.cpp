#include "../../../xpres.hpp"

bool Xpres::is_character (char let) {
  return std::isalnum(let) || let == '_' || let == '.';
}
