#include "../../../tree.hpp"
#include <cstdint>

void AVLTree::add_node (uint32_t index, float value) {
  if (!this->find(index)) {
    this->root = insert_node_AVL (index, value, this->root);
    this->many++;
  }
}
