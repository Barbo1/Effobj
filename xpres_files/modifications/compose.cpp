#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::compose(uint64_t id_1, uint64_t id_2, std::string_view name) {
  nodeEX top = this->points.top();
  if (top->type == 'p' && top->id == '+' && id_1 != id_2) {

    /* finding the id of name. */
    uint64_t id_name = 0;
    for (const auto & [n1, n2, n3]: this->token_info) {
      if (n1 == name) { goto finded; }
      id_name++;
    }
    return *this;
    finded:

    if (id_1 > id_2) { std::swap (id_1, id_2); }
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

    /* lambda functions. */
    auto cond0 = [&id_name](const nodeEX n){
      return n->type == 't' && n->id == id_name;
    };
    auto cond1 = [&](const nodeEX n){
      return n->type == 'p' && n->id == '*';
    };
    auto cond2 = [&](const nodeEX n){
      return n->type == 'p' && n->id == '/';
    };
    auto cond3 = [&](const nodeEX n){
      return n->type == 'p' && n->id == '-';
    };

    /* evaluate lambda conditions. */
    nodeEX son1c = son1, son2c = son2;
    if (cond3 (son1c)) {
      son1c = son1c->son;
    }
    if (cond3 (son2c)) {
      son2c = son2c->son;
    }
    uint16_t conds1 = cond0(son1c) | (cond1(son1c)<<1) | (cond2(son1c)<<2);
    uint16_t conds2 = cond0(son2c) | (cond1(son2c)<<1) | (cond2(son2c)<<2);
    if (!conds1 || !conds2) return *this;

    /* operations. */
    auto find_token = [&son, &id_name] (const nodeEX father) mutable {
      son = father->son;
      while (son != nullptr && (son->type != 't' || son->id != id_name)) {
        son = son->sibling;
      }
      return son;
    };
    auto quit_node = [](const nodeEX father, const nodeEX son) {
      put_first(father, son);
      if (son->sibling->sibling == nullptr) {
        father->type = son->sibling->type;
        father->id = son->sibling->id;
        father->son = son->sibling->son;
        son->sibling->son = nullptr;
        delete son->sibling;
      } else {
        father->son = son->sibling;
        son->sibling = nullptr;
      }
      delete son;
    };

    /* The switch divides the cases depending on the most presedent operator
     * of both the expresions to compose.
     * */
    nodeEX son11, son21;
    switch (conds1 | (conds2 << 3)) {
      /* two tokens. */
      case 0b001001:
        son1c->type = 'i';
        son1c->id = 1;
        son2c->type = 'i';
        son2c->id = 1;
        break;

        /* multiplication and token. */
      case 0b010001:
        std::swap (son1c, son2c);
      case 0b001010:
        if ((son11 = find_token (son1c)) == nullptr) return *this;

        quit_node (son1c, son11);
        son2c->type = 'i';
        son2c->id = 1;
        break;

        /* division and token. */
      case 0b100001:
        std::swap (son1c, son2c);
      case 0b001100:
        son11 = son1c->son;
        if (cond0 (son11)) {
          son11->type = 'i';
          son11->id = 1;
        } else if (cond1 (son11) && (son11 = find_token (son11)) != nullptr) {
          quit_node (son1c->son, son11);
        } else { 
          return *this; 
        }
        son2c->type = 'i';
        son2c->id = 1;
        break;

        /* two multiplications. */
      case 0b010010:
        son11 = find_token (son1c);
        son21 = find_token (son2c);

        if (son11 == nullptr || son21 == nullptr) return *this;

        quit_node (son2c, son21);
        quit_node (son1c, son11);
        break;

        /* division and multiplication. */
      case 0b100010:
        std::swap (son1c, son2c);
      case 0b010100:
        son21 = find_token (son2c);
        son11 = son1c->son;
        conds1 = cond0 (son11) | ((cond1 (son11) && (son11 = find_token (son11)) != nullptr) << 1);
        if (!conds1 || son21 == nullptr) { return *this; }
        switch (conds1) {
          case 1:
            son11->type = 'i';
            son11->id = 1;
            break;
          case 2:
            quit_node (son1c->son, son11);
            break;
          default:
            return *this; 
            break;
        }
        quit_node (son2c, son21);

        break;

        /* two divisions. */
      case 0b100100:
        son11 = son1c->son;
        son21 = son2c->son;
        conds1 = cond0 (son11) | ((cond1 (son11) && (son11 = find_token (son11)) != nullptr) << 1);
        conds2 = cond0 (son21) | ((cond1 (son21) && (son21 = find_token (son21)) != nullptr) << 1);
        if (!conds1 || !conds2) { return *this; }
        switch (conds1) {
          case 1:
            son11->type = 'i';
            son11->id = 1;
            break;
          case 2:
            quit_node (son1c->son, son11);
            break;
          default:
            return *this; 
            break;
        }
        switch (conds2) {
          case 1:
            son21->type = 'i';
            son21->id = 1;
            break;
          case 2:
            quit_node (son2c->son, son21);
            break;
          default:
            return *this; 
            break;
        }
        break;

      default:
        return *this;
        break;
    }

    put_first(top, son2);
    put_first(top, son1);
    if (son2->sibling == nullptr) {
      top->id = '*';
      const nodeEX _news = create_node ('t', id_name, nullptr, create_node ('p', '+'));
      _news->sibling->son = std::exchange (top->son, _news);

      if (this->points.size() < 2) { return *this; }
      this->points.pop();
      nodeEX prev_top = this->points.top();
      if (prev_top->type != 'p' || prev_top->id != '*') {
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

    } else {
      top->son = create_node (
        'p', 
        '*', 
        create_node ('t', id_name), 
        std::exchange (son2->sibling, nullptr)
      );
      son1->sibling = nullptr;
      top->son->son->sibling = deduce_operation_binary (son1, son2, '+');
    }
  }
  return *this;
}
