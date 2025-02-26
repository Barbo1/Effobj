#include "../../../xpres.hpp"

void Xpres::repetition_counter_arr_aux (
    nodeEX root, 
    const nodeEX last_son, 
    uint64_t index, 
    const uint64_t & length, 
    bool * arr
    ) noexcept {
  if (root == last_son) index = length;
  if (root != nullptr && root->type == 't') arr[index + root->id] = true;
  root = root->son;
  while (root != nullptr) {
    repetition_counter_arr_aux(root, last_son, index, length, arr);
    root = root->sibling;
  }
}

bool * Xpres::repetition_counter_arr(nodeEX root, const nodeEX last_son, uint64_t length) noexcept {
  bool * arr = new bool[length * 2]{false};
  repetition_counter_arr_aux(root, last_son, 0, length, arr);
  return arr;
}
