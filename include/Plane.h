#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include <Eigen/Core>

class Plane : public Object
{
  public:
    // Point on plane
    Eigen::Vector3d point;
    // Normal of plane
    Eigen::Vector3d normal;
  // Intersect plane with ray.
  //
  // Inputs:
  //   Ray  ray to intersect with
  //   min_t  minimum parametric distance to consider
  // Outputs:
  //   t  first intersection at ray.origin + t * ray.direction
  //   n  surface normal at point of intersection
  // Returns iff there a first intersection is found.
  bool intersect(
      const Ray& ray,
      const double min_t,
      double & t,
      Eigen::Vector3d & hit_p,
      Eigen::Vector3d & n,
      std::shared_ptr<Material> & mat,
      Eigen::Vector3d & kd,
      Eigen::Vector3d & ks,
      Eigen::Vector3d & km,
      double & p) const;
};

#endif
