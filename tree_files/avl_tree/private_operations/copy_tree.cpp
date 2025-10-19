#include "../../../tree.hpp"

template<typename T>
nodeAVL<T> copy_tree_AVL (nodeAVL<T> node) {
  nodeAVL<T> new_nd = node;
  if (new_nd != nullptr) {
    new_nd = new _node_avl<T>;
    new_nd->index = node->index;
    new_nd->value = node->value;
    new_nd->height = node->height;
    new_nd->izq = copy_tree_AVL(node->izq);
    new_nd->der = copy_tree_AVL(node->der);
  }
  return new_nd;
}

