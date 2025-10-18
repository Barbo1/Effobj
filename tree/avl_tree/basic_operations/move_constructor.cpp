#include "../../../tree.hpp"
#include <utility>

AVLTree::AVLTree (AVLTree && tree) {
  this->root = std::exchange (tree.root, nullptr);
  this->many = std::exchange (tree.many, 0);
}
