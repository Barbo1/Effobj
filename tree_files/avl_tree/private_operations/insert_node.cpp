#include "../../../tree.hpp"
#include <cstdint>

template<typename T>
nodeAVL<T> insert_node_AVL(uint32_t index, T value, nodeAVL<T> avl){
  nodeAVL<T> t = avl;
  if (t == nullptr) 
    return create_node_AVL(index, value);
  else {
    if (index > t->index) {
      t->der = insert_node_AVL (index, value, t->der);
      t->height = t->der->height + 1;
    } else {
      t->izq = insert_node_AVL(index, value, t->izq);
      t->height = t->izq->height + 1;
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
