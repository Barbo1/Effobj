#include "../../graph.hpp"

template<GraphT T>
void Graph<T>::set_vertex_value (uint32_t index, float value) {
  if (index < this->nodes_many) {
    this->vertex_values[index] = value;
  }
}
