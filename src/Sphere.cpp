#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
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

  Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
  n = hit_point - center;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

