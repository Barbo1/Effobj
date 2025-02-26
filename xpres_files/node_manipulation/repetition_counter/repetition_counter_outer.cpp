#include "../../../xpres.hpp"

bool Xpres::repetition_counter_outer(nodeEX root, const nodeEX last_son, uint64_t idold) noexcept {
  if (root != last_son) {
    bool res = root->type == 't' && root->id == idold;

    root = root->son;
    while (!res && root != nullptr) {
      res = repetition_counter_outer(root, last_son, idold); 
      root = root->sibling;
    }
    return res;
  } else return false;
}
