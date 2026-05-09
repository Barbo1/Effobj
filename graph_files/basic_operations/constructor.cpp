#include "../../graph.hpp"
#include "../../operation.hpp"

template<GraphT T>
Graph<T>::Graph (unsigned many) {
  this->vertex_values = std::vector<float> (many, 1.f);
  this->nodes_tags = primes_by_many_static (many);
  this->nodes_many = many;
  this->edges = AVLTree<float>();
}
