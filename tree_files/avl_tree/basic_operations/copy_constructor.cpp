#include "../../../tree.hpp"

template<typename T>
AVLTree<T>::AVLTree (const AVLTree & tree) {
  this->root = copy_tree_AVL(tree.root);
  this->many = tree.many;
}
