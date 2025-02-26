#include "../../worst.hpp"

nodeWS WordSet::aux_sum (nodeWS ws_1, nodeWS ws_2) {
  nodeWS res, res_prev = nullptr, res_f = nullptr;
  ws_1 = ws_1->son;
  ws_2 = ws_2->son;
  while (ws_1 != nullptr && ws_2 != nullptr) {
    if (ws_1->letter == ws_2->letter) {
      res = create_node (
        ws_1->letter, 
        ws_1->finished || ws_2->finished, 
        aux_sum(ws_1, ws_2)
      );
      ws_1 = ws_1->sibling;
      ws_2 = ws_2->sibling;
    } else if (ws_1->letter < ws_2->letter) {
      res = copy_nodes(ws_1);
      ws_1 = ws_1->sibling;
    } else {
      res = copy_nodes(ws_2);
      ws_2 = ws_2->sibling;
    }
    res_prev = 
      (res_prev == nullptr ? res_f : res_prev->sibling) = 
        res;
  }
  if (ws_2 != nullptr) {
    (res_prev == nullptr ? res_f : res_prev->sibling) = copy_nodes(ws_2, false);
  } else if (ws_1 != nullptr) {
    (res_prev == nullptr ? res_f : res_prev->sibling) = copy_nodes(ws_1, false);
  }
  return res_f;
}

WordSet WordSet::operator+(const WordSet & ws) const {
  WordSet ws_new = WordSet();
  ws_new.root->son = aux_sum(this->root, ws.root);
  return ws_new;
}
