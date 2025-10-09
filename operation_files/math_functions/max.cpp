#include "../../operation.hpp"

template<std::floating_point T> T maxv (const T& f1, const T& f2) {
  constexpr int shift = 8 * sizeof (T) - 1;
  using IntType = typename SignConst<T>::type;
  using IntTypeS = typename SignConst<T>::type_s;

  IntType c = std::bit_cast<IntType>(f1 - f2);
  c &= ~((IntTypeS)(c & SignConst<T>::value) >> shift);
  return std::bit_cast<T>(c) + f2;
}
