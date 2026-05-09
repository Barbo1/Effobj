#include "../../graph.hpp"

template<GraphT T>
uint32_t Graph<T>::vertex_number () {
  return this->vertex_values.size();
}
