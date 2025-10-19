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

template<typename T>
struct _node_avl {
  uint32_t index;
  uint32_t height;
  _node_avl<T>* izq;
  _node_avl<T>* der;
  T value;
};


template<typename T>
using nodeAVL = struct _node_avl<T>*;

template<typename T>
nodeAVL<T> create_node_AVL (uint32_t index, T value);

template<typename T>
nodeAVL<T> copy_tree_AVL (nodeAVL<T> node);

template<typename T>
int height_tree_AVL (nodeAVL<T> node);

template<typename T>
void delete_tree_AVL (nodeAVL<T> node);

template<typename T>
nodeAVL<T> insert_node_AVL (uint32_t index, T value, nodeAVL<T> node);

template<typename T>
nodeAVL<T> remove_node_AVL (uint32_t index, nodeAVL<T> node);

template<typename T>
nodeAVL<T> find_node_AVL (nodeAVL<T> node, uint32_t index);

template<typename T>
class AVLTree {
  private: 
    nodeAVL<T> root;
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

    T get_value (uint32_t);
    void set_value (uint32_t, T);

    void add_node (uint32_t, T);
    void delete_node (uint32_t);
};
