#pragma once

#include "./polynomial.hpp"
#include <vector>
#include <utility>

template <arithmetric T>
class Point {
  public:
    T x;
    T y;

    Point ();
    Point (const Point &);
    Point (Point &&);
    Point& operator= (const Point &);
    Point& operator= (Point &&);
    bool operator== (const Point &);
    ~Point ();

    Point operator+ (const Point &);
    Point operator- (const Point &);
    T operator/ (const Point &);
};

template <arithmetric T>
class PointsGroup {
  private: 
    std::vector <Point<T>> _points_;

  public:
    PointsGroup ();
    PointsGroup (const PointsGroup &);
    PointsGroup (PointsGroup &&);
    PointsGroup& operator= (const PointsGroup &);
    PointsGroup& operator= (PointsGroup &&);
    bool operator== (const PointsGroup &);
    ~PointsGroup ();

    Point<T>& operator[] (unsigned i);
    uint64_t size ();

    /* Interpolations. */
    Polynomial<T> inter_linear ();
    Polynomial<T> inter_lagrange ();

    /* Aproximations. */
    Polynomial<T> integral_aprox ();

    Polynomial<T> linear_regretion ();
    std::pair<const Point<T> &, const Point<T> &> nearest_points ();
};

template <arithmetric T>
Polynomial<T> inter_hermite ();

template <arithmetric T>
Polynomial<T> inter_splines ();
