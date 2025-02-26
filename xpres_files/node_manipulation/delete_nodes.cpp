#include "../../xpres.hpp"

void Xpres::delete_nodes (nodeEX node) noexcept {
  if (node != nullptr) {
    delete_nodes(node->sibling);
    delete_nodes(node->son); 
    delete node;
  }
}
