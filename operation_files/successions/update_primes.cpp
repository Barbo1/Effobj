#include "../../operation.hpp"
#include <cmath>
#include <cstring>

void update_primes (std::shared_ptr<int32_t[]> p, unsigned many) {
  int32_t n=p[many-1], r=std::sqrt(n), rc=r*r, *B, *T, *I, a;
  int32_t* new_arr = new int[many + 1];
  memcpy (new_arr, p.get(), many);
  p.reset (new_arr);
  B = new_arr + 3;
  T = new_arr + many;
	while (true) {
		n++;
    r += ((n - rc) ^ 0x80000000) >> 31;
    rc = r * r;
    I = B;
    a = 5;
		while (a <= r && n % a)
      a = *(I++);
    if (a > r) {
      *T = n;
      return;
    }
	}
}
