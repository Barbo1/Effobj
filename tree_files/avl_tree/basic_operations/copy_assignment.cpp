#include "../../../tree.hpp"

template<typename T>
AVLTree<T>& AVLTree<T>::operator= (const AVLTree & tree) {
  delete_tree_AVL(this->root);
  this->root = copy_tree_AVL(tree.root);
  this->many = tree.many;
  return *this;
}
