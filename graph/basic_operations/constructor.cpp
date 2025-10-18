#include "../../graph.hpp"
#include "../../operation.hpp"

Graph::Graph (unsigned many) {
  this->vertex_values = std::vector<float>(many, 0);
  this->primes = primes_by_many(many);
  this->edges = AVLTree();
}
