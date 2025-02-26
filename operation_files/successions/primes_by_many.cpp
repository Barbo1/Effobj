#include "../../operation.hpp"

std::vector<unsigned> primes_by_many (unsigned many) {
	unsigned r=3, rc=9, n=7, o=2, a, *S, *B, *T, *I;
  std::vector<unsigned> ret = std::vector<unsigned>();
  ret.resize (many);
  S = ret.data();
  B = S + 3;
  T = S + many;
	if (1 <= many) *(S++) = 2;
	if (2 <= many) *(S++) = 3;
	if (3 <= many) *(S++) = 5;
	if (4 <= many) *(S++) = 7;
	while (S < T) {
		o ^= 6;
		n += o;
	 	if (n >= rc) {
			r++;
			rc = r * r;
		}
    I = B;
    a = 5;
		while (a <= r && n % a) a = *(I++);
		if (a > r) *(S++) = n;
	}
	return ret;
}
