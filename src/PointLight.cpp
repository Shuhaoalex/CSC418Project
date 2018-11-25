#include "PointLight.h"

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  d = p - q;
  if (d.norm() > 0) {                                                                                      
    max_t = d.norm();
    d.normalize();
  } else {
    max_t = 0;
  }
}