#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::depotence() {
  nodeEX top = this->points.top();
  if (top->type == 'p' && top->id == '^') {
    nodeEX res = top->son->sibling;
    if (res->type != 'p' || res->id != '+') return *this;

    /* Transforma all the sons of res and put them in the begining of top. */
    nodeEX cop = top->son;
    nodeEX son = res->son;
    nodeEX prev = nullptr;
    top->id = '*';
    top->son = nullptr;
    cop->sibling = nullptr;

    delete res;
    while (son->sibling != nullptr) {
      top->son = create_node ('p', '^', copy_nodes (cop), top->son);
      top->son->son->sibling = prev = son;
      son = son->sibling;
      prev->sibling = nullptr;
    } 
    top->son = create_node ('p', '^', cop, top->son);
    top->son->son->sibling = son;

    /* Restruct the tree. */
    this->points.pop();
    res = this->points.top();
    if (res->type == 'p' && res->id == '*') {
      /* Quit top from the tree. */

      son = res->son;
      if (son == top) {
        res->son = top->sibling;
      } else {
        while (son->sibling != top) {
          son = son->sibling;
        }
        son->sibling = top->sibling;
      }

      /* Find the lastest son. */
      while (son->sibling != nullptr) {
        son = son->sibling;
      }

      son->sibling = top->son;
      delete top;
    } else {
      this->points.push(top);
    }
  }
  return *this;
}
