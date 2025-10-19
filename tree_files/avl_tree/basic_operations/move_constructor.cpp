#include "../../../tree.hpp"
#include <utility>

template<typename T>
AVLTree<T>::AVLTree (AVLTree && tree) {
  this->root = std::exchange (tree.root, nullptr);
  this->many = std::exchange (tree.many, 0);
}
