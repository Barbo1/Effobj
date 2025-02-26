#include "../../../xpres.hpp"

void Xpres::repetition_counter_outer_arr_aux(nodeEX root, const nodeEX last_son, bool * arr) noexcept {
  if (root != last_son) {
    if (root->type == 't') arr[root->id] = true;
    root = root->son;
    while (root != nullptr) {
      repetition_counter_outer_arr_aux(root, last_son, arr);
      root = root->sibling;
    }
  }
}

bool * Xpres::repetition_counter_outer_arr(nodeEX root, const nodeEX last_son, uint64_t length) noexcept {
  bool * arr = new bool[length]{false};
  repetition_counter_outer_arr_aux(root, last_son, arr);
  return arr;
}
