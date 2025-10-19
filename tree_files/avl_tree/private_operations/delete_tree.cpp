#include "../../../tree.hpp"

template<typename T>
void delete_tree_AVL (nodeAVL<T> node) {
  if (node != nullptr) {
    delete_tree_AVL(node->izq);
    delete_tree_AVL(node->der);
    delete node;
  }
}
