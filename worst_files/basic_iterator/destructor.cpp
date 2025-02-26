#include "../../worst.hpp"

WordSet::iterator::~iterator(){
  delete [] _nodes_;
}
