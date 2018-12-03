#include "Plane.h"
#include "Ray.h"

bool Plane::intersect(
  const Ray & ray, const double min_t, HitInfo & hit_info) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double a = (point - ray.origin).dot(normal);
  double b = ray.direction.dot(normal);
  hit_info.t = a / b;
  if (hit_info.t >= min_t) {
    hit_info.n = normal;
    hit_info.ka = this->material->ka;
    hit_info.kd = this->material->kd;
    hit_info.ks = this->material->ks;
    hit_info.km = this->material->km;
    hit_info.hit_p = hit_info.t * ray.direction + ray.origin;
    hit_info.phong_exponent = this->material->phong_exponent;
    return true;
  } else {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

