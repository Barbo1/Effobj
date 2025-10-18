#include "../../../tree.hpp"
#include <cstdint>

int AVLTree::get_height (uint32_t index) {
  nodeAVL nd = this->root;
  while (nd != nullptr && nd->index != index) {
    if (nd->index < index) nd = nd->izq;
    else nd = nd->der;
  }
  return (nd != nullptr ? nd->height : 0);
}
