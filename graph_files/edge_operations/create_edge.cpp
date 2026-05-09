#include "../../graph.hpp"
#include <cstdint>

template<GraphT T>
bool Graph<T>::create_edge (uint32_t index1, uint32_t index2) {
  if (index1 < this->vertex_values.size() && index2 < this->vertex_values.size())
    return false;
  else
    return this->edges.add_node(this->nodes_tags[index1] * this->nodes_tags[index2], 1.f);
}
