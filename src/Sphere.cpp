#include "Sphere.h"
#include "Ray.h"
bool Sphere::intersect(
  const Ray & ray, const double min_t, HitInfo & hit_info) const
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
    hit_info.t = t2;
  } else {
    hit_info.t = t1;
  }

  hit_info.hit_p = ray.origin + hit_info.t * ray.direction;
  hit_info.n = hit_info.hit_p - center;
  hit_info.ka = this->material->ka;
  hit_info.kd = this->material->kd;
  hit_info.ks = this->material->ks;
  hit_info.km = this->material->km;
  hit_info.phong_exponent = this->material->phong_exponent;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}

