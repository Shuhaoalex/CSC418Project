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
  HitInfo hit_info;
  if (first_hit(ray, min_t, objects, hit_info)) {
    rgb = blinn_phong_shading(ray, hit_info, objects, lights);
    rgb += hit_info.ka;

    Eigen::Vector3d reflected_light_color;
    Ray reflected_light;
    reflected_light.direction = reflect(ray.direction, hit_info.n);
    reflected_light.origin = hit_info.hit_p;
    reflected_light.I = ray.I * hit_info.km.mean();
    if (reflected_light.I > std::numeric_limits<double>::epsilon() * 100) {
      if (raycolor(reflected_light, 0.0001, objects, lights, num_recursive_calls + 1, reflected_light_color)){
        rgb += (reflected_light_color.array() * (hit_info.km).array()).matrix();
      }
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
