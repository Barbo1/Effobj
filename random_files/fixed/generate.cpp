#include "../../random.hpp"

uint32_t Random<FIX_MOD>::generate () {
  this->xN = this->a * this->xN + this->c;
  return this->xN;
}
