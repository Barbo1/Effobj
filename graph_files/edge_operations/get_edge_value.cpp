#include "../../graph.hpp"

template<GraphT T>
float Graph<T>::get_edge_value (uint32_t index1, uint32_t index2) {
  return this->edges.get_value(this->nodes_tags[index1] * this->nodes_tags[index2]);
}
