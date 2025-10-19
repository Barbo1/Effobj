#include "../../random.hpp"

template <_rand_type T>
uint32_t Random<T>::generate () {
  this->xN = (this->xN * this->a + this->c) % this->m;
  return this->xN;
}
