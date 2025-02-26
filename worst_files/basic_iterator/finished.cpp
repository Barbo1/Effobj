#include "../../worst.hpp"

bool WordSet::iterator::is_finished() const {
  return _large_ == -1;
}
