#include "../../graph.hpp"

template<GraphT T>
float Graph<T>::get_vertex_value (uint32_t index) {
  if (this->vertex_values.size() <= index) return 0.f;
  else return this->vertex_values[index];
}
