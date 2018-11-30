#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

#include "Object.h"
#include <Eigen/Core>
#include <memory>
#include "BoundingBox.h"
#include "Material.h"

struct MeshTriangle : public Object
{
  public:
    BoundingBox box;
    // Pointer to mesh vertex position list
    const Eigen::MatrixXd & V;
    // Pointer to mesh indices list
    const Eigen::MatrixXi & F;
    // face index
    int f;
    // Record with vertex and face set this MeshTriangle references _and_
    // compute bounding box for this triangle.
    //
    // Inputs:
    //   V  pointer to mesh vertex list
    //   F  pointer to mesh face list
    //   f  index of triangle in _F
    // Side effects: inserts this triangle into .box (see Object.h)
    inline MeshTriangle(
      const Eigen::MatrixXd & V,
      const Eigen::MatrixXi & F,
      const int f,
      const std::shared_ptr<Material> mat);
    // Object implementations (see Object.h)
    inline bool intersect(
      const Ray& ray,
      const double min_t,
      Eigen::Vector3d & hit_p,
      Eigen::Vector3d & n,
      std::shared_ptr<Material> & material,
      Eigen::Vector3d & kd,
      Eigen::Vector3d & ks,
      Eigen::Vector3d & km,
      double & p) const override;
};
#endif
