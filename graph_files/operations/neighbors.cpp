#include "../../graph.hpp"
#include <cstdint>

template<GraphT T>
std::vector<uint32_t> Graph<T>::neighbors (uint32_t index1) {
  std::vector<uint32_t> ret = std::vector<uint32_t>();
  if (this->vertex_values.size() < index1) 
    return ret;
  uint32_t prim = this->nodes_tags[index1];
  for (uint32_t i = 0; i < index1; i++)
    if (this->edges.find(this->nodes_tags[i] * prim))
      ret.push_back (i);
  for (uint32_t i = index1 + 1; i < this->nodes_many; i++)
    if (this->edges.find(this->nodes_tags[i] * prim))
      ret.push_back (i);
  return ret;
}
