#include "../../graph.hpp"
#include <utility>

template<GraphT T>
Graph<T>::Graph(Graph && g) {
  this->vertex_values = std::exchange(g.vertex_values, std::vector<float>());
  this->nodes_many = std::exchange(g.nodes_many, 0);
  this->nodes_tags = std::exchange(g.nodes_tags, nullptr);
  this->edges = std::exchange(g.edges, AVLTree<float>());
}
