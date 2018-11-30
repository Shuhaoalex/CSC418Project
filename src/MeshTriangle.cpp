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
  std::shared_ptr<Object> & descendant) const
{
  // descendant doesn't make sense so it's not touched
  return ray_intersect_triangle(
    ray,
    V.row(F(f,0)),
    V.row(F(f,1)),
    V.row(F(f,2)),
    min_t,
    max_t,
    t);
}