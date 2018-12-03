#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, HitInfo & hit_info) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool result = false;
  HitInfo temp_info;
  hit_info.t = -1;
  for (int i = 0; i < triangles.size(); i++) {
    if(triangles[i]->intersect(ray, min_t, temp_info)){
      if (hit_info.t == -1 || hit_info.t > temp_info.t) {
        hit_info = temp_info;
        result = true;
      }
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}



