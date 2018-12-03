#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>


bool Triangle::intersect(
  const Ray & ray, const double min_t, HitInfo & hit_info) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d A = V.row(F(f, 0)).transpose();
  Eigen::Vector3d B = V.row(F(f, 1)).transpose();
  Eigen::Vector3d C = V.row(F(f, 2)).transpose();
  Eigen::Vector3d AB = B - A;
  Eigen::Vector3d AC = C - A;
  hit_info.n = AB.cross(AC);

  double a = (A - ray.origin).dot(hit_info.n);
  double b = ray.direction.dot(hit_info.n);
  hit_info.t = a / b;
  if (hit_info.t < min_t) {
    return false;
  }
  hit_info.hit_p = ray.origin + hit_info.t * ray.direction;
  Eigen::Vector3d H = hit_info.hit_p;
  Eigen::Vector3d HA = A - H;
  Eigen::Vector3d HB = B - H;
  Eigen::Vector3d HC = C - H;
  double SC = (HA.cross(HB)).norm();
  double SB = (HA.cross(HC)).norm();
  double SA = (HB.cross(HC)).norm();
  // add epilon to the treshold to consider the numerical problem
  if (SA + SB + SC > hit_info.n.norm() * (1 + 2 * std::numeric_limits<double>::epsilon())) {
    return false;
  }
  Eigen::Vector3d bary(SA,SB,SC);
  bary /= bary.sum();
  hit_info.n = bary[0] * NA + bary[1] * NB + bary[2] * NC;
  hit_info.ka = this->material->ka;
  hit_info.kd = this->material->kd;
  hit_info.ks = this->material->ks;
  hit_info.km = this->material->km;
  hit_info.phong_exponent = this->material->phong_exponent;
  return true;
  ////////////////////////////////////////////////////////////////////////////
}


