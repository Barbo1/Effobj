#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
nodeAVL<T> create_node_AVL (uint32_t index, T value) {
  nodeAVL<T> new_nd = new _node_avl<T>;
  new_nd->height = 1;
  new_nd->value = value;
  new_nd->index = index;
  new_nd->izq = nullptr;
  new_nd->der = nullptr;
  return new_nd;
}
