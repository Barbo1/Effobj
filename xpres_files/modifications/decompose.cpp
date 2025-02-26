#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::descompose(uint64_t id_1 = 0, uint64_t id_2 = 1) {
  nodeEX top = this->points.top();
  if (top->type == 'p' && id_1 != id_2) {

    /* discerning element to decompose over. */
    bool over_2 = id_1 > id_2;
    if (over_2) { std::swap (id_1, id_2); } 
    nodeEX son;

    /* finding the first node. */
    son = top->son;
    while (son != nullptr && id_1 != 0) {
      id_1--;
      id_2--;
      son = son->sibling;
    }
    if (son == nullptr) return *this;
    nodeEX son1 = son;

    /* finding the second node. */
    son = son->sibling;
    id_2--;
    while (son != nullptr && id_2 != 0) {
      id_2--;
      son = son->sibling;
    }
    if (son == nullptr) return *this;
    nodeEX son2 = son;

    if (over_2) { std::swap (son1, son2); }

    /* discriminating cases: */
    nodeEX sum;
    switch (top->id) {
      case '*':
        if (son1->type != 'p') { return *this; }
        switch (son1->id) {
          case '+':
            sum = son1;
            break;
          case '-':
          case '/':
            sum = son1->son;
            while (sum != nullptr && sum->type == 'p' && sum->id == '-') { sum = sum->son; }
            if (sum == nullptr || sum->type != 'p' || sum->id != '+') { return *this; }
            break;
          default:
            return *this;
        }
        break;
      case '/':
        sum = son1;
        while (sum != nullptr && sum->type == 'p' && sum->id == '-') { sum = sum->son; }
        if (sum == nullptr || sum->type != 'p' || sum->id != '+') { return *this; }
        break;
      default:
        return *this;
    }
fin_switch:

    /* change tree. */
    nodeEX sum1 = sum->son;
    nodeEX prev = nullptr, sib;
    while (sum1 != nullptr) {
      sib = std::exchange (sum1->sibling, nullptr);
      sum1 = 
        (prev == nullptr ? sum->son : prev->sibling) = 
        deduce_operation_binary (
            (over_2 ? copy_nodes (son2) : sum1), 
            (over_2 ? sum1 : copy_nodes (son2)), 
            top->id
            );
      sum1->sibling = sib;
      prev = std::exchange (sum1, sum1->sibling);
    }

    /* keep the expression valid. */
    put_first(top, son2);
    top->son = son2->sibling;
    son2->sibling = nullptr;
    delete_nodes (son2);

    if (top->son == son1 && son1->sibling == nullptr && !is_oper_u(top->id)) {
      top->id = son1->id;
      top->type = son1->type;
      nodeEX _news = top->son = son1->son;
      delete son1;

      if (this->points.size() < 2) { return *this; }
      this->points.pop();
      nodeEX prev_top = this->points.top();
      if (prev_top->type != 'p' || prev_top->id != '+' || top->type != 'p' || top->id != '+') {
        this->points.push(top);
        return *this;
      }
      son = prev_top->son;
      if (son == top) {
        _news->sibling->sibling = top->sibling;
        prev_top->son = _news;
      } else {
        while (son->sibling != top) {
          son = son->sibling;
        }
        _news->sibling->sibling = top->sibling;
        son->sibling = _news;
      }
      delete top;

      /* When I try to use the same iterator that is returned from this function, it throws a memory
       * error. By now it is not posible to utilize it. */
    }
  }
  return *this;
}
