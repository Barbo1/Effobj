#include "../../xpres.hpp"

nodeEX Xpres::copy_nodes (nodeEX node, bool not_same_level) noexcept {
  if (node == nullptr) return nullptr;
  nodeEX node_new = create_node(node->type, node->id, copy_nodes(node->son, false), nullptr);
  node_new->sibling = 
    not_same_level ? 
      nullptr : 
      copy_nodes(node->sibling, false);
  return node_new;
}
