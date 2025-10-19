#include "../../random.hpp"

template <_rand_type T>
void Random<T>::discompress_primes (uint32_t E, uint32_t* S, uint32_t* N) {
  if (E <= 1) {
    S[0] = 1;
    S[1] = E;
    return;
  }

  uint16_t P = 1, q; 

  /* iteration in prime 2: */
  q = ~E & (E - 1);
  q = (q & 0x55555555) + ((q >> 1) & 0x55555555);
  q = (q & 0x33333333) + ((q >> 2) & 0x33333333);
  q = (q & 0x0F0F0F0F) + ((q >> 4) & 0x0F0F0F0F);
  q = (q & 0x00FF00FF) + ((q >> 8) & 0x00FF00FF);
  q = (q & 0x0000FFFF) + ((q >> 16) & 0x0000FFFF);
  if (q > 0) {
    S [P++] = 2;
    E >>= q;
  }

  /* iteration in prime 3: */
  if (E != 1) {
    q = gcd_primes (E, 0xCFD41B91);
    if (q > 1) {
      S [P++] = 3;
      E /= q;
    }
  }

  /* iteration with the rest of the numbers. */
  uint32_t o = 2, i = 0, n = *N;
  while (E != 1) {
    /* finding new. */
    o ^= 6;
    n += o;
    while (n >= bound[i]) {
      i++;
    }

    /* finding greater potence. */
    q = 1;
    for (int j = 0; j < 13-i; j++) {
      q *= n;
    }

    /* testing if can divide E. */
    q = gcd_primes (E, q);
    if (q > 1) {
      S [P++] = n;
      E /= q;
    }
  }
  *N = n;
  S[0] = P;
}
