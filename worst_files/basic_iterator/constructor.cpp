#include "../../worst.hpp"

WordSet::iterator::iterator () {
  _nodes_ = new nodeWS[MAX_LEN_WORD];
  _large_ = -1;
}
