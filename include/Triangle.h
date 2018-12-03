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
    const int f;
    const Eigen::RowVector3d NA;
    const Eigen::RowVector3d NB;
    const Eigen::RowVector3d NC;
    inline Triangle(
      Eigen::MatrixXd & _V,
      Eigen::MatrixXi & _F,
      const int _f,
      Eigen::RowVector3d _NA,
      Eigen::RowVector3d _NB,
      Eigen::RowVector3d _NC
    ): V(_V), F(_F), f(_f), NA(_NA), NB(_NB), NC(_NC) {
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
