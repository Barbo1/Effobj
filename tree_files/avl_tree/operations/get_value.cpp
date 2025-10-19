#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
T AVLTree<T>::get_value (uint32_t index) {
  nodeAVL<T> nd = this->root;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  return (nd != nullptr ? nd->value : 0);
}
