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

