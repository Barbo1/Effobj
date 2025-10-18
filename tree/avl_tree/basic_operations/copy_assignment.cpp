#include "../../../tree.hpp"

AVLTree& AVLTree::operator= (const AVLTree & tree) {
  delete_tree_AVL(this->root);
  this->root = AVLTree::copy_tree_AVL(tree.root);
  this->many = tree.many;
  return *this;
}
