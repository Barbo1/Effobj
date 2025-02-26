#include "../../worst.hpp"

[[nodiscard("Discarding node creation")]] nodeWS WordSet::copy_nodes (nodeWS node, bool first) {
  if (node != nullptr) {
    return create_node (
        node->letter, 
        node->finished, 
        copy_nodes (node->son , false),
        (first ? nullptr: copy_nodes (node->sibling, false))
      );
  }
  return nullptr;
}
