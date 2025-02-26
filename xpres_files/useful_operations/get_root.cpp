#include "../../xpres.hpp"

inline nodeEX get_root (std::stack<nodeEX> st_this) {
  nodeEX root;

  while (!st_this.empty()) {
    root = st_this.top();
    st_this.pop();
  }

  return root;
}

