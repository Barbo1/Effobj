#pragma once

#include "./tree.hpp"
#include <cstdint>
#include <vector>
#include <memory>

/* This class implements undirected graphs. It uses AVL trees to store the edges with its values,
 * so operations like searching are guaranteed to be made in O(log(n)). Given e as the number of
 * edges ans v the number of vertex, the order of memory used is O(v + e). The order time of the
 * operations are:
 *  - graph creation -> O(v * log(v)) [i suppose, but technically i must count also e * log(e)]
 *  - create_edge -> O(log(e))
 *  - remove_edge -> O(log(e))
 *  - edge_number -> O(1)
 *  - set_vertex_val -> O(1)
 *  - get_vertex_val -> O(1)
 *  - get_edge_val -> O(log(e))
 *  - set_edge_val -> O(log(e))
 *  - neighbors -> O(v * log(e)), could be made in O(e)
 *  - adjacents -> O(log(e))
 *  - create_vertex -> O(v)
 *
 *  Deletion of a vertex is something particularly inconsistent with the representation, in which
 *  is have edges from 1 to n exactly. The deletion will make sense if i change the [1 ... n] to
 *  [1...(i-1) (i+1)...n], changing [(i+1)...n] to [i...(n-1)]. This operation will take 
 *  O(v * log(e) + e) apparently.
 * */

enum class GraphT {
  DIRECT,
  UNDIRECT
};

template <GraphT T>
class Graph {
  private:
    uint32_t nodes_many;
    std::shared_ptr<int32_t[]> nodes_tags;
    AVLTree<float> edges;
    std::vector<float> vertex_values;

  public:
    Graph (uint32_t);
    Graph (const Graph &);
    Graph (Graph &&);
    Graph& operator= (const Graph &);
    Graph& operator= (Graph &&);

    bool create_edge (uint32_t, uint32_t);
    bool remove_edge (uint32_t, uint32_t);
    bool is_edge (uint32_t, uint32_t);
    uint32_t edge_number ();
    float get_edge_value (uint32_t, uint32_t);
    void set_edge_value (uint32_t, uint32_t, float);

    void create_vertex ();
    uint32_t vertex_number ();
    void set_vertex_value (uint32_t, float);
    float get_vertex_value (uint32_t);

    std::vector<uint32_t> neighbors (uint32_t);
    bool adjacents (uint32_t, uint32_t);

    /* Not yet implemented. */

    std::vector<uint32_t> shortest_path (uint32_t, uint32_t);
    bool is_flow_net ();
    Graph find_min_flow ();
    Graph power (int);
};


/* This class implements directed graphs. All the memory stored is O(e + v). The order time of the
 * operations are the same as the above implementation, save the followings:
 *  - graph creation -> O(v) [i suppose, but technically i must count also e * log(e)]
 *  - neighbors -> O(log(e)), could be made in O(e)
 * */

template<>
class Graph<GraphT::DIRECT> {
  private:
    std::vector<AVLTree<float>> edges;
    std::vector<float> vertex_values;

  public:
    Graph (uint32_t);
    Graph (const Graph &);
    Graph (Graph &&);
    Graph& operator= (const Graph &);
    Graph& operator= (Graph &&);

    bool create_edge (uint32_t, uint32_t);
    bool remove_edge (uint32_t, uint32_t);
    bool is_edge (uint32_t, uint32_t);
    uint32_t edge_number ();
    float get_edge_value (uint32_t, uint32_t);
    void set_edge_value (uint32_t, uint32_t, float);

    void create_vertex ();
    uint32_t vertex_number ();
    void set_vertex_value (uint32_t, float);
    float get_vertex_value (uint32_t);

    std::vector<uint32_t> neighbors (uint32_t);
    bool adjacents (uint32_t, uint32_t);

    /* Not yet implemented. */

    std::vector<uint32_t> shortest_path (uint32_t, uint32_t);
    bool is_flow_net ();
    Graph find_min_flow ();
    Graph power (int);
};
