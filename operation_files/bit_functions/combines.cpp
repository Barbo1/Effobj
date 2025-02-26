#include "../../operation.hpp"

template<typename T> 
requires std::is_integral_v<T> 
constexpr T combines (T seq1, T seq2, unsigned point) {
  T r = (1 << point) - 1;
  return seq1 & r | seq2 & ~r;
}
