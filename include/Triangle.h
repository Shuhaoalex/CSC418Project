#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"
#include "insert_triangle_into_box.h"
#include <Eigen/Core>

#include<iostream>

class Triangle : public Object
{
  public:
    const Eigen::MatrixXd & V;
    const Eigen::MatrixXi & F;
    const Eigen::MatrixXd & N;
    const Eigen::MatrixXi & FN;
    int f;
    inline Triangle(
      Eigen::MatrixXd & _V,
      Eigen::MatrixXi & _F,
      Eigen::MatrixXd & _N,
      Eigen::MatrixXi & _FN,
      const int _f
    ): V(_V), F(_F), N(_N), FN(_FN), f(_f) {
      insert_triangle_into_box(V.row(F(f, 0)),
                               V.row(F(f, 1)),
                               V.row(F(f, 2)),
                               this->box);
    }
    // Intersect a triangle with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    bool intersect(
      const Ray & ray, const double min_t, HitInfo & hit_info) const;
};

#endif
