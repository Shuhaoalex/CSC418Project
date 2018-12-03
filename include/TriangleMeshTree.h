#ifndef MESHTREE_H
#define MESHTREE_H

#include "BoundingBox.h"
#include "MeshTriangle.h"
#include <Eigen/Core>
#include <memory>
#include <vector>

// Implementation
#include "ray_intersect_box.h"

class TriangleMeshTree : public Object, public std::enable_shared_from_this<TriangleMeshTree>
{
  public:
    std::shared_ptr<Object> left;
    std::shared_ptr<Object> right;

    TriangleMeshTree(
      const std::vector<std::shared_ptr<Object> > & triangles);
    bool intersect(
      const Ray& ray,
      const double min_t,
      double & t,
      Eigen::Vector3d & hit_p,
      Eigen::Vector3d & n,
      std::shared_ptr<Material> & material,
      Eigen::Vector3d & kd,
      Eigen::Vector3d & ks,
      Eigen::Vector3d & km,
      double & p) const;
};

#endif
