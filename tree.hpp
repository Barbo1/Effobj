#pragma once
#include "./needed.hpp"

/* Tree2
 * TreeN
 * TreeAVL
 * BTree
 * BpTree
 * Heap
 * */
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
