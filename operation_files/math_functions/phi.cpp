#include "../../operation.hpp"

unsigned phi (unsigned n) {
  if (n < 2) return 1;
  std::array<unsigned, 33> A = discompress_primes(n);
  for (int i = 1; i < A[0]; i++) {
    n /= A[i];
    n *= A[i]-1;
  }
  return n;
}
