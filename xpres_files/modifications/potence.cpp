#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::potence(uint64_t id_1, uint64_t id_2) {
  nodeEX top = this->points.top();
  if (top->type == 'p' && top->id == '*' && id_1 != id_2) {
    if (id_1 > id_2) { std::swap (id_1, id_2); } 

    /* finding the first node. */
    nodeEX son1 = top->son;
    while (son1 != nullptr && id_1 != 0) {
      id_1--;
      id_2--;
      son1 = son1->sibling;
    }
    if (son1 == nullptr) return *this;

    /* finding the second node. */
    nodeEX son2 = son1->sibling;
    id_2--;
    while (son2 != nullptr && id_2 != 0) {
      id_2--;
      son2 = son2->sibling;
    }
    if (son2 == nullptr) return *this;

    bool c1 = son1->type == 'p' && son1->id == '^';
    bool c2 = son2->type == 'p' && son2->id == '^';

    /* there are four cases. */
    if (c1 && c2) {
      if (!compare_tree_equal(son1->son, son2->son, true)) { return *this; }

      /* put first both. */
      put_first (top, son2);
      put_first (top, son1);

      top->son = son2;
      son2->son->sibling = deduce_operation_binary(son1->son->sibling, son2->son->sibling, '+');
      son1->son->sibling = nullptr;
      delete_nodes (son1->son);
      delete son1;

    } else if (c1) {
      if (!compare_tree_equal(son1->son, son2, true)) { return *this; }

      /* put first both. */
      put_first (top, son2);
      put_first (top, son1);

      son1->son->sibling = deduce_operation_binary(son1->son->sibling, create_node ('i', 1), '+');
      son1->sibling = son2->sibling;
      son2->sibling = nullptr;
      delete_nodes (son2);

    } else if (c2) {
      if (!compare_tree_equal(son2->son, son1, true)) { return *this; }

      /* put first both. */
      put_first (top, son1);
      put_first (top, son2);

      son2->son->sibling = deduce_operation_binary(son2->son->sibling, create_node ('i', 1), '+');
      son2->sibling = son1->sibling;
      son1->sibling = nullptr;
      delete_nodes (son1);

    } else if (compare_tree_equal(son2, son1, true)) {
      /* put first both. */
      put_first (top, son2);
      put_first (top, son1);

      if (son2->sibling == nullptr) {
        top->id = '^';
      } else {
        top->son = create_node ('p', '^', son1, son2->sibling);
        son2->sibling = nullptr;
      }
      son2->type = 'i';
      son2->id = 2;
    }
  }
  return *this;
}
