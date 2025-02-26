#include "../../worst.hpp"

WordSet::iterator::iterator (const WordSet & ws) {
  nodeWS tr = ws.root;
  _large_ = 0;
  _nodes_ = new nodeWS[MAX_LEN_WORD];
  while (tr->son != nullptr && !tr->finished) {
    _nodes_[_large_++] = tr = tr->son;
  }
  _large_--;
}
