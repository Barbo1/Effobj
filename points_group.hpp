#pragma once

#include "./polynomial.hpp"
#include <vector>
#include <utility>

class Point {
  public:
    float x, y;

    Point ();
    Point (const Point &);
    Point (Point &&);
    Point& operator= (const Point &);
    Point& operator= (Point &&);
    bool operator== (const Point &);
    ~Point ();

    Point operator+ (const Point &);
    Point operator- (const Point &);
    float operator/ (const Point &);
};

class PointsGroup {
  private: 
    std::vector <Point> _points_;

  public:
    PointsGroup ();
    PointsGroup (const PointsGroup &);
    PointsGroup (PointsGroup &&);
    PointsGroup& operator= (const PointsGroup &);
    PointsGroup& operator= (PointsGroup &&);
    bool operator== (const PointsGroup &);
    ~PointsGroup ();

    Point& operator[] (unsigned i);
    uint64_t size ();

    /* Interpolations. */
    Polynomial inter_linear ();
    Polynomial inter_lagrange ();

    /* Aproximations. */
    Polynomial integral_aprox ();

    Polynomial linear_regretion ();
    std::pair<const Point &, const Point &> nearest_points ();
};

Polynomial inter_hermite ();
Polynomial inter_splines ();
