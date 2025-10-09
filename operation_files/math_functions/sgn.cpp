#include "../../operation.hpp"

template<std::floating_point T> T sgnv (T& f1) {
  using IntType = typename SignConst<T>::type;

  T fr = f1;
  IntType * c = (IntType *)&fr;
  *c &= SignConst<T>::value;
  *c |= SignConst<T>::one;
  return fr;
}

template<std::floating_point T> T&& sgnv (T&& f1) {
  using IntType = typename SignConst<T>::type;

  IntType * c = (IntType *)&f1;
  *c &= SignConst<T>::value;
  *c |= SignConst<T>::one;
  return f1;
}
