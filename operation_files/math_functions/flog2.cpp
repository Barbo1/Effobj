#include "../../operation.hpp"

template<typename R, typename T> 
requires std::is_integral_v<T> && std::is_fundamental_v<R>
constexpr R flog2 (T x) {
  constexpr int s = sizeof (T);
  int n = 0;
  if constexpr (s >= 64) {
    if (x > 0x00000000FFFFFFFF) { n += 32; x = x>>32; }
  }
  if constexpr (s >= 32) {
    if (x > 0x0000FFFF) { n += 16; x = x>>16; }
  }
  if constexpr (s >= 16) {
    if (x > 0x00FF) { n += 8; x = x>>8; }
  }
  if (x > 0x000F) { n += 4; x = x>>4; }
  if (x > 0x0003) { n += 2; x = x>>2; }
  if (x > 0x0001) n += 1;
  return s;
}
