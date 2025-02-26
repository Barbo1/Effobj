#include "../../operation.hpp"

std::array<unsigned, 33> discompress_primes(unsigned E) {
  std::array<unsigned, 33> S;
  unsigned char P = 1, i; 
  unsigned r = 2, n = 2;
  bool b = true;
  if (E == 0) {
    S[0] = 1;
    S[1] = 0;
    return S;
  }
  while (E != 1) {
    i = 1;
    r += n == r*r;
    while (i < P && S[i] <= r && (b = n % S[i])) {
      i++;
    }
    if (!(E % n) && b) {
      S[P] = n;
      P++; 
      while (!(E % n)) {
        E /= n;
      }
    }
    n++;
  }
  S[0] = P;
  return S;
}
