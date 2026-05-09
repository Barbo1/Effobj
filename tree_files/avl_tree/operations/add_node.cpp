#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
bool AVLTree<T>::add_node (uint32_t index, T value) {
  bool cond = !this->find(index);
  if (cond) {
    this->root = insert_node_AVL (index, value, this->root);
    this->many++;
  }
  return cond;
}
