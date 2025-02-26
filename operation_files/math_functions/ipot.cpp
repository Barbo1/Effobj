#include "../../operation.hpp"

template<typename T>
requires Multipliable<T>
constexpr T ipot (const T & obj, int32_t pot) {
  if (pot == 1) return obj;

  int32_t l2 = flog2<int32_t> (pot), i;
  T last;
  T * arr = new T[l2];
  arr[0] = obj;
  for (i = 0; i < l2-1; i++) {
    arr[i+1] = arr[i] * arr[i];
  }
  last = arr[i] * arr[i];
  for (i = l2-1; i >= 0; i--) {
    if ((1 << i) & pot) {
      last *= arr[i];
    }
  }
  delete [] arr;
  return last;
}
