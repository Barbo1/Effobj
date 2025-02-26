#include "../../xpres.hpp"

Xpres::iterator& Xpres::iterator::operator[](int64_t index) {
  nodeEX son = this->points.top()->son;
  if (index >= 0) {
    while (son != nullptr && index-- > 0) { son = son->sibling; }
    if (son != nullptr) { this->points.push(son); }
  } else {
    while (!this->points.empty() && index++ < 0) { this->points.pop(); }
  }
  return *this;
}
