#include "insert_triangle_into_box.h"
#include "ray_intersect_triangle.h"
#include "MeshTriangle.h"

inline MeshTriangle::MeshTriangle(
    const Eigen::MatrixXd & _V,
    const Eigen::MatrixXi & _F,
    const int _f,
    const std::shared_ptr<Material> mat): V(_V), F(_F), f(_f)
{
  insert_triangle_into_box(
    V.row(F(f,0)),
    V.row(F(f,1)),
    V.row(F(f,2)),
    box);
  this->material = mat;
}

// Simple wrapper around `ray_intersect_triangle`
inline bool MeshTriangle::intersect(
  const Ray& ray,
  const double min_t,
  double & t,
  Eigen::Vector3d & hit_p,
  Eigen::Vector3d & n,
  std::shared_ptr<Material> & mat,
  Eigen::Vector3d & kd,
  Eigen::Vector3d & ks,
  Eigen::Vector3d & km,
  double & p) const
{
  // descendant doesn't make sense so it's not touched
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
}