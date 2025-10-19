#include "../../operation.hpp"

std::shared_ptr<int32_t[]> primes_by_many_static (unsigned many) {
  int32_t r=3, rc=9, n=7, *S, *B, *T, *I, o=2, a;
  std::shared_ptr<int32_t[]> ret(new int[many]);
  S = ret.get();
  B = S + 3;
  T = S + many;
	if (1 <= many) *(S++) = 2;
	if (2 <= many) *(S++) = 3;
	if (3 <= many) *(S++) = 5;
	if (4 <= many) *(S++) = 7;
	while (S < T) {
		o ^= 6;
		n += o;
    r += ((n - rc) ^ 0x80000000) >> 31;
    rc = r * r;
    I = B;
    a = 5;
		while (a <= r && n % a)
      a = *(I++);
    *S = n;
    S -= (r - a) >> 31;
	}
	return ret;
}
