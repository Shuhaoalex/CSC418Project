#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double a = (point - ray.origin).dot(normal);
  double b = ray.direction.dot(normal);
  t = a / b;
  if (t >= min_t) {
    n = normal;
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

