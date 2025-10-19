#include "../../../tree.hpp"
#include <utility>

template<typename T>
AVLTree<T>& AVLTree<T>::operator= (AVLTree && tree) {
  delete_tree_AVL(this->root);
  this->root = std::exchange (tree.root, nullptr);
  this->many = std::exchange (tree.many, 0);
  return *this;
}

