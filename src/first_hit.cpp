#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  // int & hit_id, 
  // double & t,
  // Eigen::Vector3d & n,
  double & t,
  Eigen::Vector3d & hit_point,
  Eigen::Vector3d & n,
  std::shared_ptr<Material> & material,
  Eigen::Vector3d & kd,
  Eigen::Vector3d & ks,
  Eigen::Vector3d & km,
  double & p)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool result = false;
  t = -1;
  double temp_t, temp_p;
  Eigen::Vector3d temp_hitp, temp_n, temp_kd, temp_ks, temp_km;
  std::shared_ptr<Material> temp_material;
  for (int i = 0; i < objects.size(); i++) {
    if(objects[i]->intersect(ray, min_t, temp_t, temp_hitp, temp_n, temp_material, temp_kd, temp_ks, temp_km, temp_p)){
      if (t == -1 || t > temp_t) {
        t = temp_t;
        hit_point  = temp_hitp;
        n = temp_n;
        material = temp_material;
        kd = temp_kd;
        ks = temp_ks;
        km = temp_km;
        p = temp_p;
        result = true;
      }
    }
  }
  n.normalize();
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

