#include "../../graph.hpp"

void Graph::set_edge_val (uint32_t index1, uint32_t index2, float value) {
  nodeAVL<_edges_types> nd = find_node_AVL(
    this->edges, this->primes[index1] * this->primes[index2]
  );
  if (nd != nullptr) {
    nd->value.value = value;
  }
}
