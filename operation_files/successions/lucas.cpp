#include "../../operation.hpp"

std::vector<int> lucas (int P, int Q, int x0, int x1, unsigned many) {
  std::vector<int> ret = std::vector<int>();
  ret.resize (many);
  int * data = ret.data ();
  int * top = data + many;
  
  int prev1 = *(data++) = x0;
  int prev2 = *(data++) = x1;

  while (data < top) {
    prev2 = std::exchange (
      prev1, 
      *(data++) = P * prev1 - Q * prev2
    );
  }

  return ret;
}
