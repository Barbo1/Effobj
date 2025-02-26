#include "../../xpres.hpp"

nodeEX Xpres::create_node (uint8_t type, uint64_t id, nodeEX son, nodeEX sibling) noexcept {
  nodeEX new_node = new exp_struct;
  new_node->type = type;
  new_node->id = id;
  new_node->son = son;
  new_node->sibling = sibling;
  return new_node;
}
