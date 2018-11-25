#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int hit_id;
  double hit_t;
  Eigen::Vector3d hit_n;
  if (first_hit(ray, min_t, objects, hit_id, hit_t, hit_n)) {
    std::shared_ptr<Material> obj_material = objects[hit_id]->material;
    rgb = blinn_phong_shading(ray, hit_id, hit_t, hit_n, objects, lights);
    rgb += obj_material->ka;

    Eigen::Vector3d reflected_light_color;
    Ray reflected_light;
    reflected_light.direction = reflect(ray.direction, hit_n);
    reflected_light.origin = ray.origin + hit_t * ray.direction;
    if (std::pow(obj_material->km(0), num_recursive_calls) > std::numeric_limits<double>::epsilon() * 100) {
      if (raycolor(reflected_light, 0.0001, objects, lights, num_recursive_calls + 1, reflected_light_color)){
        rgb += (reflected_light_color.array() * (obj_material->km).array()).matrix();
      }
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
