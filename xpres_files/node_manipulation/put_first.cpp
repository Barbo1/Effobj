#include "../../xpres.hpp"

void Xpres::put_first (const nodeEX father, nodeEX sontc) noexcept {
  nodeEX prev = father->son;
  if (prev != sontc) {
    while (prev->sibling != sontc) {
      prev = prev->sibling;
    }
    prev->sibling = sontc->sibling;
    sontc->sibling = father->son;
    father->son = sontc;
  }
}
