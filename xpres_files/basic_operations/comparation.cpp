#include "../../xpres.hpp"

bool Xpres::operator==(const Xpres & exp) const noexcept {
  if (exp.token_info.size() != this->token_info.size()) { return false; }
  return compare_tree_similar(exp.root, this->root, this->token_info.size());
}
