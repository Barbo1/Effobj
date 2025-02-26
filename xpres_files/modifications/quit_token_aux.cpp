#include "../../xpres.hpp"

bool quit_token_aux(nodeEX root, const uint64_t idname, bool recalculate_ids) {
  if (root->type == 't') {
    if (recalculate_ids && root->id > idname) {
      root->id--;
      return false;
    } else {
      return root->id == idname;
    }
  } else if (root->son != nullptr) {
    nodeEX son = root->son;
    nodeEX prev = nullptr;
    nodeEX res;
    while (son != nullptr) {
      if (quit_token_aux(son, idname, recalculate_ids)) {
        res = son;
        son = son->sibling;
        if (res->son != nullptr) {
          (prev == nullptr ? root->son : prev->sibling) = res->son;
          res->son->sibling = son;
        } else {
          (prev == nullptr ? root->son : prev->sibling) = son;
        }
        delete res;
      } else {
        prev = son;
        son = son->sibling;
      }
    }
    return root->son->sibling == nullptr && !(
        root->type == 'p' && (root->id == '-' || root->id == '!' || root->id == '|') ||
        root->type == 'f'
        );
  }
  return false;
}
