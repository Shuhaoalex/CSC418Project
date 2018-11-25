#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool result = false;
  double temp_t;
  t = -1;
  Eigen::Vector3d temp_n;
  for (int i = 0; i < objects.size(); i++) {
    if(objects[i]->intersect(ray, min_t, temp_t, temp_n)){
      if (t == -1 || t > temp_t) {
        t = temp_t;
        n = temp_n;
        hit_id = i;
        result = true;
      }
    }
  }
  n.normalize();
  return result;
  ////////////////////////////////////////////////////////////////////////////
}

