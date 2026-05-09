#include "../../graph.hpp"

template<GraphT T>
Graph<T>& Graph<T>::operator=(const Graph & g) {
  this->vertex_values = g.vertex_values;
  this->nodes_tags = g.nodes_tags;
  this->nodes_many = g.nodes_many;
  this->edges = g.edges;
  return *this;
}
