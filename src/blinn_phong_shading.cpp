#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const Eigen::Vector3d & hit_point,
  const Eigen::Vector3d & n,
  const Eigen::Vector3d & kd,
  const Eigen::Vector3d & ks,
  const double & p,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // std::shared_ptr<Material> obj_material = objects[hit_id]->material;
  // Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
  Eigen::Vector3d result(0.0,0.0,0.0);
  // Eigen::Vector3d hit_norm = n.normalized();

  for (int i = 0; i < lights.size(); i++) {
    Eigen::Vector3d direction_to_light;
    double max_t;
    lights[i]->direction(hit_point, direction_to_light, max_t);

    // This part is to compute the shading of the light
    if (!check_shade(objects, hit_point, direction_to_light, std::numeric_limits<double>::epsilon()*1000, max_t)) {
      double multiplier;

      // This part is to compute the Lambertien shading
      multiplier = n.dot(direction_to_light);
      result += (kd.array() * (lights[i]->I).array()).matrix() * ((0<multiplier)?multiplier:0);

      // This part is to compute the specular color
      Eigen::Vector3d h = (direction_to_light - ray.direction.normalized()).normalized();
      multiplier = n.dot(h);
      result += (ks.array() * (lights[i]->I).array()).matrix() * pow(((0<multiplier)?multiplier:0), p);
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}
