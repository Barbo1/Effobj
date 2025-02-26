#include "../../worst.hpp"

nodeWS WordSet::aux_great(nodeWS node, unsigned n, unsigned & top){
  nodeWS sons_iter, res, res_prev = nullptr, res_f = nullptr;
  sons_iter = node->son;
  if (n == top) return copy_nodes(sons_iter, false);
  n++;
  while (sons_iter != nullptr) {
    res = aux_great(sons_iter, n, top);
    if (res != nullptr) {
      res_prev = 
        (res_f == nullptr ? res_f : res_prev->sibling) = 
          create_node (sons_iter->letter, false, res);
    }
    sons_iter = sons_iter->sibling;
  }
  return res_f;
}

WordSet WordSet::operator>(unsigned base_lenght) const {
  WordSet ws = WordSet();
  ws.root->son = aux_great(this->root, 0, base_lenght);
  return ws;
}
