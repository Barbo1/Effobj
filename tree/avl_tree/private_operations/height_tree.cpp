#include "../../../tree.hpp"

int AVLTree::height_tree_AVL (nodeAVL node) {
  if (node != nullptr)
    return node->height;
  return 0;
}
