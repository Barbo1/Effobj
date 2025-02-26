#include "../../xpres.hpp"

std::vector<nodeEX> Xpres::get_array_sons (nodeEX father) noexcept {
  std::vector<nodeEX> vec;
  vec.reserve (20);
  father = father->son;
  while (father != nullptr) {
    vec.push_back (father);
    father = father->sibling;
  }
  return vec;
}
