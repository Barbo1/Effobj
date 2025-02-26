#include "../../worst.hpp"

nodeWS WordSet::aux_int (nodeWS ws_1, nodeWS ws_2){
  nodeWS res, res1, res_prev = nullptr, res_f = nullptr;
  ws_1 = ws_1->son;
  ws_2 = ws_2->son;
  while (ws_1 != nullptr && ws_2 != nullptr) {
    if (ws_1->letter == ws_2->letter) {
      if ((res1 = aux_int(ws_1, ws_2)) != nullptr || (ws_1->finished && ws_2->finished)) {
        res_prev = 
          (res_prev == nullptr ? res_f : res_prev->sibling) = 
            create_node (
              ws_1->letter, 
              ws_1->finished && ws_2->finished, 
              res1
            );
      }
      ws_1 = ws_1->sibling;
      ws_2 = ws_2->sibling;
    } else if (ws_1->letter < ws_2->letter) {
      ws_1 = ws_1->sibling;
    } else {
      ws_2 = ws_2->sibling;
    }
  }
  return res_f;
}

WordSet WordSet::operator*(const WordSet & ws) const {
  WordSet ws_new = WordSet();
  ws_new.root->son = aux_int(this->root, ws.root);
  return ws_new;
}
