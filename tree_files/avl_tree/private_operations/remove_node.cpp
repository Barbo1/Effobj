#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
nodeAVL<T> remove_node_AVL (uint32_t index, nodeAVL<T> avl){
  nodeAVL<T> t = avl;
  if (index == t->index) {
    delete t;
    return nullptr;
  } else {
    if (index > t->index) {
      t->der = remove_node_AVL (index, t->der);
      t->height = height_tree_AVL (t->der) - 1;
    } else {
      t->izq = remove_node_AVL (index, t->izq);
      t->height = height_tree_AVL (t->izq) - 1;
    }
    nodeAVL<T> b = nullptr;
    switch (height_tree_AVL(t->izq) - height_tree_AVL(t->der)) {
      case 2:
        b = t->izq;
        switch (height_tree_AVL(b->izq) - height_tree_AVL(b->der)) {
          case 1:
            t->izq = b->der;
            b->der = t;
            break;
          case -1:
            t->izq = b->der;
            b->der = t->izq->izq;
            t->izq->izq = b;
            b = t->izq;
            t->izq = b->der;
            b->der = t;
            b->height++;
            b->izq->height--;
            break;
          defalut:
            break;
        }
        t->height-=2;
        return b;
        break;
      case -2:
        b = t->der;
        switch (height_tree_AVL(b->der) - height_tree_AVL(b->izq)) {
          case 1:
            t->der = b->izq;
            b->izq = t;
            break;
          case -1:
            t->der = b->izq;
            b->izq = t->der->der;
            t->der->der = b;
            b = t->der;
            t->der = b->izq;
            b->izq = t;
            b->height++;
            b->der->height--;
            break;
          default:
            break;
        }
        t->height-=2;
        return b;
        break;
      default:
        break;
    }
    return t;
  }
}
