#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
void AVLTree<T>::delete_node (uint32_t index) {
  if (this->find(index)) {
    this->root = remove_node_AVL (index, this->root);
    this->many--;
  }
}
