#include "../../../tree.hpp"

void AVLTree::delete_tree_AVL (nodeAVL node) {
  if (node != nullptr) {
    delete_tree_AVL(node->izq);
    delete_tree_AVL(node->der);
    delete node;
  }
}
