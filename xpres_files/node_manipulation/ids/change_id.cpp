#include "../../../xpres.hpp"

void Xpres::change_id (const uint64_t idold, const uint64_t idnew, nodeEX last_son) noexcept {
  if (last_son != nullptr) {
    if (last_son->type == 't' && last_son->id == idold) {
      last_son->id = idnew;
    }

    last_son = last_son->son;
    while (last_son != nullptr) {
      change_id(idold, idnew, last_son);
      last_son = last_son->sibling;
    }
  }
}
