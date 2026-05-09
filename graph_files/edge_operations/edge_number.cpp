#include "../../graph.hpp"

template<GraphT T>
uint32_t Graph<T>::edge_number () {
  return this->edges.nodes_number();
}
