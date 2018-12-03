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
  std::shared_ptr<Material> mat;
  double t, p;
  Eigen::Vector3d hit_p, n, kd, ks, km;
  if (first_hit(ray, min_t, objects, t, hit_p, n, mat, kd, ks, km, p)) {
    rgb = blinn_phong_shading(ray, hit_p, n, kd, ks, p, objects, lights);
    rgb += kd * 0.1;

    Eigen::Vector3d reflected_light_color;
    Ray reflected_light;
    reflected_light.direction = reflect(ray.direction, n);
    reflected_light.origin = hit_p;
    if (std::pow(km(0), num_recursive_calls) > std::numeric_limits<double>::epsilon() * 100) {
      if (raycolor(reflected_light, 0.0001, objects, lights, num_recursive_calls + 1, reflected_light_color)){
        rgb += (reflected_light_color.array() * km.array()).matrix();
      }
    }
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
