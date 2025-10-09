#include "../../operation.hpp"

template<typename T>
struct SignConst;

template<>
struct SignConst<float> {
  using type = uint32_t;
  using type_s = int32_t;
  static constexpr type value = 0x80000000;
  static constexpr type one = 0x3F800000;
};

template<>
struct SignConst<double> {
  using type = uint64_t;
  using type_s = int64_t;
  static constexpr type value = 0x8000000000000000;
  static constexpr type one = 0x3FF0000000000000;
};
