#include "../../../tree.hpp"

AVLTree::~AVLTree () {
  delete_tree_AVL(this->root);
}
