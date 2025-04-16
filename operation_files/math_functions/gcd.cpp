#include "../../operation.hpp"

uint32_t gcd (uint32_t n, uint32_t m) {
  int64_t t;
  uint32_t q = n | m;
  q = ~q & (q - 1);
  q = (q & 0x55555555) + ((q >> 1) & 0x55555555);
  q = (q & 0x33333333) + ((q >> 2) & 0x33333333);
  q = (q & 0x0F0F0F0F) + ((q >> 4) & 0x0F0F0F0F);
  q = (q & 0x00FF00FF) + ((q >> 8) & 0x00FF00FF);
  q = (q & 0x0000FFFF) + ((q >> 16) & 0x0000FFFF);
  m >>= q; 
  n >>= q; 

  if ((n & 1) == 1) { t = -(int64_t)m; goto B4; }
  else t = n;
B3:
  t = t >> 1;
B4:
  if ((t & 1) == 0) goto B3;
  if (t > 0) n = t;
  else m = -t;
  t = n - (int64_t)m;
  if (t != 0) goto B3;

  return n * (1 << q);
}
