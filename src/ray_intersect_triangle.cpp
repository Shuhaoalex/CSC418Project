#include "ray_intersect_triangle.h"
bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  double & t,
  Eigen::Vector3d & n,
  Eigen::Vector3d & hit_p,
  Eigen::Vector3d & bary) {
    Eigen::Vector3d cA = A.transpose();
    Eigen::Vector3d cB = B.transpose();
    Eigen::Vector3d cC = C.transpose();

    Eigen::Vector3d AB = cB - cA;
    Eigen::Vector3d AC = cC - cA;
    n = AB.cross(AC);

    double a = (cA - ray.origin).dot(n);
    double b = ray.direction.dot(n);
    t = a / b;
    if (t < min_t) {
        return false;
    }
    Eigen::Vector3d H = ray.origin + t * ray.direction;
    hit_p = H;
    Eigen::Vector3d HA = cA - H;
    Eigen::Vector3d HB = cB - H;
    Eigen::Vector3d HC = cC - H;
    double SC = HA.cross(HB).norm();
    double SB = HA.cross(HC).norm();
    double SA = HB.cross(HC).norm();
    // add epilon to the treshold to consider the numerical issue
    if ((SA + SB + SC) > n.norm() * (1 + 2 * std::numeric_limits<double>::epsilon())) {
        return false;
    }
    bary << SA, SB, SC;
    bary = bary/bary.sum();
    return true;
  }