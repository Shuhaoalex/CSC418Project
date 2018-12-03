#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const HitInfo & hit_info,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // std::shared_ptr<Material> obj_material = objects[hit_id]->material;
  Eigen::Vector3d hit_point = hit_info.hit_p;
  Eigen::Vector3d result(0.0,0.0,0.0);
  Eigen::Vector3d hit_norm = hit_info.n;

  for (int i = 0; i < lights.size(); i++) {
    Eigen::Vector3d direction_to_light;
    double max_t;
    lights[i]->direction(hit_point, direction_to_light, max_t);

    // This part is to compute the shading of the light
    Ray light_ray;
    light_ray.origin = hit_point;
    light_ray.direction = direction_to_light;
    HitInfo temp_info;
    
    if (!first_hit(light_ray, std::numeric_limits<double>::epsilon()*1000, objects, temp_info) || temp_info.t > max_t) {
      double multiplier;

      // This part is to compute the Lambertien shading
      multiplier = hit_norm.dot(direction_to_light);
      result += ((hit_info.kd).array() * (lights[i]->I).array()).matrix() * ((0<multiplier)?multiplier:0);

      // This part is to compute the specular color
      Eigen::Vector3d h = (direction_to_light - ray.direction.normalized()).normalized();
      multiplier = hit_norm.dot(h);
      result += ((hit_info.ks).array() * (lights[i]->I).array()).matrix() * pow(((0<multiplier)?multiplier:0), hit_info.phong_exponent);
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}
