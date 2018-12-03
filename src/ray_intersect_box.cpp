#include "ray_intersect_box.h"
bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t) {
    double d, a;
    double tmin = -std::numeric_limits<double>::infinity();
    double tmax = std::numeric_limits<double>::infinity();

    for (int i = 0; i < 3; i++) {
        d = ray.direction[i];
        a = 1 / d;
        if (a >= 0) {
        tmin = fmax(a * (box.min_corner[i] - ray.origin[i]), tmin);
        tmax = fmin(a * (box.max_corner[i] - ray.origin[i]), tmax);
        } else {
        tmin = fmax(a * (box.max_corner[i] - ray.origin[i]), tmin);
        tmax = fmin(a * (box.min_corner[i] - ray.origin[i]), tmax);
        }
    }
    tmin = fmax(tmin, min_t);
    if (tmin > tmax || tmin == std::numeric_limits<double>::infinity()) {
        return false;
    }
    return true;
  }