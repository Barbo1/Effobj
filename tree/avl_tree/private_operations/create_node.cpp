#include "../../../tree.hpp"
#include <cstdint>

nodeAVL AVLTree::create_node_AVL (uint32_t index, float value) {
  nodeAVL new_nd = new _node_avl;
  new_nd->height = 1;
  new_nd->value = value;
  new_nd->index = index;
  new_nd->izq = nullptr;
  new_nd->der = nullptr;
  return new_nd;
}
