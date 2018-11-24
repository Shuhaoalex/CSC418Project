#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <math.h>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  std::shared_ptr<Material> obj_material = objects[hit_id]->material;
  Eigen::Vector3d hit_point = ray.origin + t * ray.direction;
  Eigen::Vector3d result(0.0,0.0,0.0);
  Eigen::Vector3d hit_norm = n.normalized();

  for (int i = 0; i < lights.size(); i++) {
    Eigen::Vector3d direction_to_light;
    double max_t;
    lights[i]->direction(hit_point, direction_to_light, max_t);

    // This part is to compute the shading of the light
    Ray light_ray;
    light_ray.origin = hit_point;
    light_ray.direction = direction_to_light;
    int hit;
    double t_temp;
    Eigen::Vector3d n_temp;
    if (!first_hit(light_ray, std::numeric_limits<double>::epsilon()*1000, objects, hit, t_temp, n_temp) || t_temp > max_t) {
      double multiplier;

      // This part is to compute the Lambertien shading
      multiplier = hit_norm.dot(direction_to_light);
      result += ((obj_material->kd).array() * (lights[i]->I).array()).matrix() * ((0<multiplier)?multiplier:0);

      // This part is to compute the specular color
      Eigen::Vector3d h = (direction_to_light - ray.direction.normalized()).normalized();
      multiplier = hit_norm.dot(h);
      result += ((obj_material->ks).array() * (lights[i]->I).array()).matrix() * pow(((0<multiplier)?multiplier:0), obj_material->phong_exponent);
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}
