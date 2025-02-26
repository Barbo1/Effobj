#include "../../../xpres.hpp"

nodeEX Xpres::recalculate_ids (nodeEX node, uint64_t * arr) noexcept { 
  if (node != nullptr) {
    if (node->type == 't') node->id = arr[node->id];
    recalculate_ids(node->son, arr);
    recalculate_ids(node->sibling, arr);
  }
  return node;
}
