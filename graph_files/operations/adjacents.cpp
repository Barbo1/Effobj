#include "../../graph.hpp"

template<GraphT T>
bool Graph<T>::adjacents (uint32_t index1, uint32_t index2) {
  return 
    index1 < this->vertex_values.size() && 
    index2 < this->vertex_values.size() && 
    this->edges.find(this->nodes_tags[index1] * this->nodes_tags[index2]);
}


