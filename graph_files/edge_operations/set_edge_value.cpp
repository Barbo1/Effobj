#include "../../graph.hpp"

template<GraphT T>
void Graph<T>::set_edge_value (uint32_t index1, uint32_t index2, float value) {
  this->edges.set_value(this->nodes_tags[index1] * this->nodes_tags[index2], value);
}
