#include "../../random.hpp"

Random<FIX_MOD>::Random (uint32_t seed) {
  /* Calculating c... */
  this->c = 1;
  for (int i = 0; i < 16; i++) {
    if (seed & (1 << i)) {
      this->c *= relatives[i];
    }
  }

  /* Calculating a... */
  this->a = 2;
  seed = (~seed >> 5) + 0x0000FFFF;
  for (int i = 16; i < 32; i++) {
    if (seed & (1 << i)) {
      this->a *= relatives[i];
    }
  }
  this->a += 1;

  /* Set xN to 0... */
  this->xN = 0;
}
