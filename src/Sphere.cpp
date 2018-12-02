#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
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
  double a = ray.direction.dot(ray.direction);
  double b = (ray.origin - center).dot(ray.direction);
  double c = (ray.origin - center).dot(ray.origin - center) - radius * radius;
  double delta = b * b - a * c;
  if (delta < 0) {
    return false;
  }
  delta = sqrt(delta);
  double t1 = (-b - delta) / a;
  double t2 = (-b + delta) / a;
  if (t2 < min_t) {
    return false;
  }
  if (t1 < min_t) {
    t = t2;
  } else {
    t = t1;
  }

  hit_p = ray.origin + t * ray.direction;
  n = (hit_point - center).normalized()
  mat = this->material;
  kd = this->material->kd;
  ks = this->material->ks;
  km = this->material->km;
  p = this->material->phong_exponent;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

