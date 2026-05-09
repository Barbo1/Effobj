#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
bool AVLTree<T>::delete_node (uint32_t index) {
  bool cond = this->find(index);
  if (cond) {
    this->root = remove_node_AVL (index, this->root);
    this->many--;
  }
  return cond;
}
