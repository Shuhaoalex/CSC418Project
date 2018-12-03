#ifndef MESH_TRIANGLE_H
#define MESH_TRIANGLE_H

#include "Object.h"
#include <Eigen/Core>
#include <memory>
#include "BoundingBox.h"
#include "Material.h"
#include "ray_intersect_triangle.h"
#include "insert_triangle_into_box.h"
#include <algorithm>

class MeshTriangle : public Object
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
    MeshTriangle(
      const Eigen::MatrixXd & _V,
      const Eigen::MatrixXi & _F,
      const int _f,
      const std::shared_ptr<Material> mat): V(_V), F(_F), f(_f){
        insert_triangle_into_box(
          V.row(F(f,0)),
          V.row(F(f,1)),
          V.row(F(f,2)),
          box);
        this->material = mat;
      }
    // Object implementations (see Object.h)
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
      double & p) const {
        Eigen::Vector3d bary;
        if (ray_intersect_triangle(
          ray,
          V.row(F(f,0)),
          V.row(F(f,1)),
          V.row(F(f,2)),
          min_t,
          t,
          n,
          hit_p,
          bary
        )) {
          mat = this->material;
          kd = this->material->kd;
          ks = this->material->ks;
          km = this->material->km;
          p = this->material->phong_exponent;
          return true;
        }
        return false;
      };
};
#endif
