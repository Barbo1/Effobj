#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
bool AVLTree<T>::set_value (uint32_t index, T value) {
  nodeAVL<T> nd = this->root;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  bool cond = nd != nullptr;
  if (cond)
    nd->value = value;
  return cond;
}
