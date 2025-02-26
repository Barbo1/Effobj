#pragma once

#include "./needed.hpp"
#include <vector>

typedef struct _node_avl * nodeAVL;

template <typename T>
class Graph {
protected:
    std::vector<T> _data_;
    std::vector<nodeAVL> _adjacency_;
public:
    Graph ();
    Graph (uint32_t);
    Graph (const Graph &);
    Graph (Graph &&);
    Graph & operator= (const Graph &) = 0;
    Graph & operator= (Graph &&) = 0;
    bool operator== (const Graph &) = 0;
    virtual ~Graph (){};

    virtual void create_edge () = 0;
    virtual void remove_edge (uint32_t, uint32_t) = 0;
    virtual uint32_t edge_quan () = 0;
    virtual bool adjacents (uint32_t, uint32_t) = 0;
    virtual std::vector<uint32_t> neighbors (uint32_t) = 0;
    virtual void set_vertex_val (uint32_t, T) = 0;
    virtual void set_edge_val (uint32_t, uint32_t, T) = 0;
    virtual T get_vertex_val (uint32_t) = 0;
    virtual T get_edge_val (uint32_t, uint32_t) = 0;

    virtual std::vector<uint32_t> shortest_path (uint32_t, uint32_t) = 0;
    virtual Graph complement () = 0; 
};

template <typename T>
class GraphDirected : public Graph<T> {
public:
    GraphDirected find_topology (); 
    GraphDirected trasnpose (); 
};

template <typename T>
class GraphUndirected : public Graph<T> {
public:
    bool is_flow_net ();
    GraphUndirected find_min_flow ();
    GraphUndirected power (int);
};
