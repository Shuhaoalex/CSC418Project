#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  bool result = false;
  double temp_t;
  t = -1;
  Eigen::Vector3d temp_n;
  for (int i = 0; i < triangles.size(); i++) {
    if(triangles[i]->intersect(ray, min_t, temp_t, temp_n)){
      if (t == -1 || t > temp_t) {
        t = temp_t;
        n = temp_n;
        result = true;
      }
    }
  }
  return result;
  ////////////////////////////////////////////////////////////////////////////
}



