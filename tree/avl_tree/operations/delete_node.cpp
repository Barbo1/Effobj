#include "../../../tree.hpp"
#include <cstdint>

void AVLTree::delete_node (uint32_t index) {
  if (this->find(index)) {
    this->root = remove_node_AVL (index, this->root);
    this->many--;
  }
}
