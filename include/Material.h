#ifndef MATERIAL_H
#define MATERIAL_H
#include <Eigen/Core>
#include <vector>

// Blinn-Phong Approximate Shading Material Parameters
struct Material
{
  // Diffuse, Specular, Mirror Color
  Eigen::Vector3d kd,ks,km;
  // Phong exponent
  double phong_exponent;
  // bool use_UV;
  // int UV_width;
  // int UV_height;
  // std::vector<double> UV;
  // bool will_refract;
  // double refraction_rate;
  // double color_satuate_rate;
};
#endif
