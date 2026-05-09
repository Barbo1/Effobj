#include "../../graph.hpp"

template<GraphT T>
bool Graph<T>::is_edge (uint32_t index1, uint32_t index2) {
  return this->edges.find(this->nodes_tags[index1] * this->nodes_tags[index2]);
}
