#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
void AVLTree<T>::add_node (uint32_t index, T value) {
  if (!this->find(index)) {
    this->root = insert_node_AVL (index, value, this->root);
    this->many++;
  }
}
