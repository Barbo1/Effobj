#include "../../../xpres.hpp"

void Xpres::add_ids (nodeEX root, uint64_t n) noexcept {
  if (root != nullptr) {
    if (root->type == 't') root->id += n;
    add_ids (root->son, n);
    add_ids (root->sibling, n);
  }
}
