#ifndef MATERIAL_H
#define MATERIAL_H
#include <Eigen/Core>
#include <vector>

// Blinn-Phong Approximate Shading Material Parameters
struct Material
{
  // Ambient, Diffuse, Specular, Mirror Color
  Eigen::Vector3d ka,kd,ks,km;
  // Phong exponent
  double phong_exponent;
  bool use_UV;
  std::vector<char> UV;
  bool will_refract;
  double refraction_rate;
};
#endif
