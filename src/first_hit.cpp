#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  HitInfo & hit_info)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool result = false;
  HitInfo temp_info;
  hit_info.t = -1;
  for (int i = 0; i < objects.size(); i++) {
    if(objects[i]->intersect(ray, min_t, temp_info)){
      if (hit_info.t == -1 || hit_info.t > temp_info.t) {
        hit_info = temp_info;
        hit_info.n.normalize();
        result = true;
      }
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}

bool check_shade(
  const std::vector< std::shared_ptr<Object> > & objects,
  const Eigen::Vector3d & hit_point,
  const Eigen::Vector3d & direction,
  double min_t,
  double max_t  
) {
  Ray light_ray(hit_point, direction);
  double t, temp_p;
  Eigen::Vector3d temp_hitp, temp_n, temp_kd, temp_ks, temp_km;
  std::shared_ptr<Material> material;
  bool temp = first_hit(light_ray, min_t, objects, t, temp_hitp, temp_n, material, temp_kd, temp_ks, temp_km, temp_p);
  return temp && t <= max_t;
}

