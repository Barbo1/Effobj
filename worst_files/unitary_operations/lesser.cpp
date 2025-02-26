#include "../../worst.hpp"

nodeWS WordSet::aux_less(nodeWS node, unsigned n, unsigned & top){
  nodeWS sons_iter, res, res_prev = nullptr, res_f = nullptr;
  sons_iter = node->son;
  if (n++ < top) {
    while (sons_iter != nullptr) {
      res = aux_less(sons_iter, n, top);
      if (res != nullptr) res_prev = (res_f == nullptr ? res_f : res_prev->sibling) = res;
      sons_iter = sons_iter->sibling;
    }
    if (res_f != nullptr || node->finished) {
      res = create_node (node->letter, node->finished, res_f);
    }
    return res;
  }
  return nullptr;
}

WordSet WordSet::operator<(unsigned top_lenght) const {
  WordSet ws = WordSet();
  ws.root->son = aux_less(this->root, 0, top_lenght);
  return ws;
}
