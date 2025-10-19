#include "../../../tree.hpp"

template<typename T>
AVLTree<T>::~AVLTree () {
  delete_tree_AVL(this->root);
}
