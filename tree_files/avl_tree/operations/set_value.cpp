#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
void AVLTree<T>::set_value (uint32_t index, T value) {
  nodeAVL<T> nd = this->root;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  nd->value = value;
}
