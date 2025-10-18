#include "../../../tree.hpp"
#include <cstdint>

void AVLTree::set_value (uint32_t index, float value) {
  nodeAVL nd = this->root;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  nd->value = value;
}
