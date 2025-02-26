#include "../../operation.hpp"

void moreComplexSieve(std::vector<unsigned>& initial_primes, unsigned limit) {
  bool * mark = new bool[limit];
  for (unsigned i = 0; i < limit; i++) {
    mark[i] = i & 1;
  }
  for (unsigned i = 9; i < limit; i += 3) {
    mark[i] = false;
  }
  for (unsigned p=5, o=2; p*p<limit; p+=o, o^=6) {
    if (mark[p]) {
      for (unsigned i=p*p; i<limit; i+=p) {
        mark[i] = false;
      }
    }
  }

  initial_primes.push_back (2);
  initial_primes.push_back (3);
  for (unsigned p=5, o=2; p<limit; p+=o, o^=6) {
    if (mark[p]) {
      initial_primes.push_back (p);
    }
  }
  delete [] mark;
}

std::vector<unsigned> primes_by_bound (unsigned top) { 
  unsigned limit = floor (sqrt (top)) + 1;
  std::vector<unsigned> initial_primes;
  initial_primes.reserve (limit);
  moreComplexSieve (initial_primes, limit);

  std::vector<unsigned> reminding_primes;
  reminding_primes.reserve (top - limit);

  unsigned size = limit;
  bool mark[limit];
  unsigned high = limit*2;

  for (unsigned low = limit; low < top; low += limit) {
    if (high > top) {
      high = top;
      size = high - low;
    }

    memset (mark, true, size);
    for (auto p: initial_primes) {
      for (unsigned i = ((low - 1)/p + 1) * p; i < high; i += p) {
        mark [i-low] = false;
      }
    }

    for (unsigned i = 0; i < size; i++) {
      if (mark[i]) {
        reminding_primes.push_back(i + low);
      }
    }

    high += limit;
  }

  initial_primes.insert(initial_primes.end(), reminding_primes.begin(), reminding_primes.end());
  return initial_primes;
}
