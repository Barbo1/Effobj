#include "../../xpres.hpp"

bool Xpres::change_tree(const uint64_t idold, nodeEX node_exp, nodeEX last_son) noexcept {
  if (last_son != nullptr) {
    if (last_son->type == 't' && last_son->id == idold) {
      return true;
    }

    nodeEX father = last_son;
    nodeEX last_son_prev = nullptr;
    nodeEX copia;
    last_son = last_son->son;
    while (last_son != nullptr) {
      if (change_tree(idold, node_exp, last_son)) {
        copia = copy_nodes(node_exp);
        last_son_prev != nullptr ? 
          last_son_prev->sibling :
          father->son = copia;
        copia->sibling = last_son->sibling;
        delete last_son;
        last_son_prev = copia;
        last_son = copia->sibling;
      } else {
        last_son_prev = last_son;
        last_son = last_son->sibling;
      }
    }
  }
  return false;
}
