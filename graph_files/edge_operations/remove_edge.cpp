#include "../../graph.hpp"

template<GraphT T>
bool Graph<T>::remove_edge (uint32_t index1, uint32_t index2) {
  if (index1 < this->vertex_values.size() && index2 < this->vertex_values.size())
    return false;
  else 
    return this->edges.delete_node(this->nodes_tags[index1] * this->nodes_tags[index2]);
}
