#include "../../random.hpp"

template <_rand_type T>
uint32_t gcd_primes (uint32_t n, uint32_t m) {
  int64_t t;
  goto B5; 
B3:
  t >>= 1;
B4:
  if ((t & 1) == 0) { goto B3; }
  if (t > 0) { n = t; }
  else { m = -t; }
B5:
  t = n - (int64_t)m;
  if (t != 0) { goto B3; }

  return n;
}
