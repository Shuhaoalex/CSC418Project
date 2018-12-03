#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include <Eigen/Core>
#include <memory>
#include "BoundingBox.h"

struct Ray;
class Object
{
  public:
    std::shared_ptr<Material> material;
    BoundingBox box;
    // https://stackoverflow.com/questions/461203/when-to-use-virtual-destructors
    // Intersect object with ray.
    //
    // Inputs:
    //   Ray  ray to intersect with
    //   min_t  minimum parametric distance to consider
    // Outputs:
    //   t  first intersection at ray.origin + t * ray.direction
    //   n  surface normal at point of intersection
    // Returns iff there a first intersection is found.
    //
    // The funny = 0 just ensures that this function is defined (as a no-op)
    virtual bool intersect(
      const Ray& ray,
      const double min_t,
      double & t,
      Eigen::Vector3d & hit_p,
      Eigen::Vector3d & n,
      std::shared_ptr<Material> & mat,
      Eigen::Vector3d & kd,
      Eigen::Vector3d & ks,
      Eigen::Vector3d & km,
      double & p) const = 0;
    // virtual Eigen::Vector3d get_kd(Eigen::Vector2d & p) const = 0;
};

#endif
