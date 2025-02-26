#include "../../operation.hpp"

template<typename T> 
requires std::is_integral_v<T> 
constexpr bool bitsp (T x) {
  constexpr int s = sizeof (T);
  if constexpr (s >= 64) {
    x = x >> 32 ^ x;
  }
  if constexpr (s >= 32) { 
    x = x >> 16 ^ x;
  }
  if constexpr (s >= 16) { 
    x = x >> 8 ^ x;
  }
  x = x >> 4 ^ x;
  x = x >> 2 ^ x;
  x = x >> 1 ^ x;
  return x & 1;
}
