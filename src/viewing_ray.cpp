#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  double pix_width = camera.width/width;
  double pix_height = camera.height/height;
  float mid_pix_x = width/2.0 - 0.5;
  float mid_pix_y = height/2.0 - 0.5;
  Eigen::Vector3d direction((j - mid_pix_x)*pix_width, (mid_pix_y - i)*pix_height, -camera.d);
  ray.origin = camera.e;
  ray.direction = direction[0] * camera.u + direction[1] * camera.v + direction[2] * camera.w;
  ////////////////////////////////////////////////////////////////////////////
}

