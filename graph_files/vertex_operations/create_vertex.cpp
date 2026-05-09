#include "../../graph.hpp"
#include "../../operation.hpp"

template<GraphT T>
void Graph<T>::create_vertex () {
  update_primes (this->nodes_tags, this->nodes_many);
  this->vertex_values.push_back (1.f);
  this->nodes_many++;
}
