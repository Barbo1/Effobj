#include "../../../tree.hpp"

template<typename T>
int height_tree_AVL (nodeAVL<T> node) {
  if (node != nullptr)
    return node->height;
  return 0;
}
