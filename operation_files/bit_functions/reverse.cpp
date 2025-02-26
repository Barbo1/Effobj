#include "../../operation.hpp"

template<typename T> 
requires std::is_integral_v<T>
constexpr T reverse (T x) {
  constexpr int s = sizeof (T);
  if constexpr (s > 32) {
    T t;
    x = (x << 32) | (x >> 32);
    x = (x & 0x0001FFFF0001FFFFLL) << 15 | (x & 0xFFFE0000FFFE0000LL) >> 17;
    t = (x ^ (x >> 10)) & 0x003F801F003F801FLL;
    x = (t | (t << 10)) ^ x;
    t = (x ^ (x >> 4)) & 0x0E0384210E038421LL;
    x = (t | (t << 4)) ^ x;
    t = (x ^ (x >> 2)) & 0x2248884222488842LL;
    x = (t | (t << 2)) ^ x;
  } else if constexpr (s > 16) {
    x = (x & 0x55555555) << 1 | (x >> 1) & 0x55555555;
    x = (x & 0x33333333) << 2 | (x >> 2) & 0x33333333;
    x = (x & 0x0F0F0F0F) << 4 | (x >> 4) & 0x0F0F0F0F;
    x = (x << 24) | ((x & 0xFF00) << 8) | ((x >> 8) & 0xFF00) | (x >> 24);
    return x;
  } else if constexpr (s > 8) {
    x = (x & 0x5555) << 1 | (x >> 1) & 0x5555;
    x = (x & 0x3333) << 2 | (x >> 2) & 0x3333;
    x = (x & 0x0F0F) << 4 | (x >> 4) & 0x0F0F;
    x = (x & 0xFF00) << 8 | (x >> 8) & 0xFF00;
    return x;
  } else  {
    x = (x & 0x55) << 1 | (x >> 1) & 0x55;
    x = (x & 0x33) << 2 | (x >> 2) & 0x33;
    x = (x & 0x0F) << 4 | (x >> 4) & 0x0F;
    return 0;
  }
}
