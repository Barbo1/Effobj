#include "../../../tree.hpp"

AVLTree::AVLTree (const AVLTree & tree) {
  this->root = AVLTree::copy_tree_AVL(tree.root);
  this->many = tree.many;
}
