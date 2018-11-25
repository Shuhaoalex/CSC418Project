#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d A = std::get<0>(corners);
  Eigen::Vector3d B = std::get<1>(corners);
  Eigen::Vector3d C = std::get<2>(corners);
  Eigen::Vector3d AB = B - A;
  Eigen::Vector3d AC = C - A;
  n = AB.cross(AC);

  double a = (A - ray.origin).dot(n);
  double b = ray.direction.dot(n);
  t = a / b;
  if (t < min_t) {
    return false;
  }
  Eigen::Vector3d H = ray.origin + t * ray.direction;
  Eigen::Vector3d HA = A - H;
  Eigen::Vector3d HB = B - H;
  Eigen::Vector3d HC = C - H;
  Eigen::Vector3d S1 = HA.cross(HB);
  Eigen::Vector3d S2 = HA.cross(HC);
  Eigen::Vector3d S3 = HB.cross(HC);
  // add epilon to the treshold to consider the numerical problem
  if (S1.norm() + S2.norm() + S3.norm() > n.norm() * (1 + 2 * std::numeric_limits<double>::epsilon())) {
    return false;
  }
  return true;
  ////////////////////////////////////////////////////////////////////////////
}


