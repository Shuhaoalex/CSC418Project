#ifndef HITINFO_H
#define HITINFO_H
#include <Eigen/Core>

// Blinn-Phong Approximate Shading Material Parameters
struct HitInfo
{
  // Ambient, Diffuse, Specular, Mirror Color
  Eigen::Vector3d ka,kd,ks,km,n,hit_p;
  // Phong exponent
  double phong_exponent,t;
};
#endif
