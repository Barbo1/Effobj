#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
nodeAVL<T> find_node_AVL (nodeAVL<T> node, uint32_t index) {
  nodeAVL<T> nd = node;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  return nd;
}
