#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
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
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double a = (point - ray.origin).dot(this->normal);
  double b = ray.direction.dot(this->normal);
  t = a / b;
  if (t >= min_t) {
    hit_p = ray.origin + t * ray.direction;
    n = this->normal;
    mat = this->material;
    kd = this->material->kd;
    ks = this->material->ks;
    km = this->material->km;
    p = this->material->phong_exponent;
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

