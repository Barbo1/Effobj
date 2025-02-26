#include "../../worst.hpp"

nodeWS WordSet::aux_sub(nodeWS ws_1, nodeWS ws_2){
  nodeWS res, son_prev = nullptr, son_f = nullptr;
  ws_1 = ws_1->son;
  ws_2 = ws_2->son;
  while (ws_1 != nullptr && ws_2 != nullptr) {
    if (ws_1->letter == ws_2->letter) {
      if ((res = aux_sub(ws_1, ws_2)) != nullptr || (ws_1->finished && !ws_2->finished)) {
        son_prev = 
          (son_prev == nullptr ? son_f : son_prev->sibling) = 
            create_node (
              ws_1->letter, 
              ws_1->finished && !ws_2->finished, 
              res
            );
      }
      ws_1 = ws_1->sibling;
      ws_2 = ws_2->sibling;
    } else if (ws_1->letter < ws_2->letter) {
      son_prev = 
        (son_prev == nullptr ? son_f : son_prev->sibling) = 
          copy_nodes(ws_1);
      ws_1 = ws_1->sibling;
    } else {
      ws_2 = ws_2->sibling;
    }
  }
  if (ws_1 != nullptr) {
    (son_prev == nullptr ? son_f : son_prev->sibling) = 
      copy_nodes(ws_1, false);
  }
  return son_f;
}

WordSet WordSet::operator-(const WordSet & ws) const {
  WordSet ws_new = WordSet();
  ws_new.root->son = aux_sub(this->root, ws.root);
  return ws_new;
}
