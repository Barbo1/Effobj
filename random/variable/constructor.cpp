#include "../../random.hpp"

template <_rand_type T>
Random<T>::Random (uint32_t m) {
  this->m = m;
  uint32_t n = 1;
  uint32_t divisors[17];
  discompress_primes (m, divisors, &n);

  /* calculating a... */
  this->a = 1;
  for (uint8_t i = 0; i < divisors[0]; i++) {
    this->a *= divisors[i];
  }
  if ((~m & 0x0003) == 0x0003) {
    this->a *= 2;
  }
  this->a++;

  /* calculating c... */
  uint16_t res = 1, j = 1;
  bool a;
  n += 10;
  while (gcd (m, n) != 1) {
    n++;
  }
  this->c = n;

  /* set x0... */
  this->xN = 0;
}
