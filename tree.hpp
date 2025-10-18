#pragma once

#include <cstdint>
#include <sys/types.h>

template<typename T>
struct _node_tree {
  uint32_t index, height;
  T value;
  _node_tree<T>* izq;
  _node_tree<T>* der;
};

template<typename T>
using nodeTREE = _node_tree<T>*;

template <typename T> class Tree {
  private: 
    
  public:
    Tree ();
    Tree (const Tree &);
    Tree (Tree &&);
    Tree & operator= (const Tree &);
    Tree & operator= (Tree &&);
    bool operator== (const Tree &);

    virtual bool add_element (T elem);
    virtual bool del_element (T elem);
    virtual T find_element (T elem);

    virtual int get_heigth ();
    virtual int get_elems ();

    ~Tree ();
};

struct _node_avl {
  uint32_t index, height;
  float value;
  _node_avl* izq;
  _node_avl* der;
};

using nodeAVL = struct _node_avl*;

class AVLTree {
  private: 
    static nodeAVL create_node_AVL (uint32_t index, float value);
    static nodeAVL copy_tree_AVL (nodeAVL node);

    static int height_tree_AVL (nodeAVL node);
    static void delete_tree_AVL (nodeAVL node);

    static nodeAVL insert_node_AVL (uint32_t index, float value, nodeAVL node);
    static nodeAVL remove_node_AVL (uint32_t index, nodeAVL node);
    
    nodeAVL root;
    uint32_t many;

  public:
    AVLTree ();
    AVLTree (const AVLTree &);
    AVLTree (AVLTree &&);
    AVLTree & operator= (const AVLTree &);
    AVLTree & operator= (AVLTree &&);
    ~AVLTree ();

    uint32_t nodes_number ();
    int get_height (uint32_t);

    bool find (uint32_t);

    float get_value (uint32_t);
    void set_value (uint32_t, float);

    void add_node (uint32_t, float);
    void delete_node (uint32_t);
};
