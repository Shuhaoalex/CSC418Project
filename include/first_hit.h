#ifndef FIRST_HIT_H
#define FIRST_HIT_H

#include "Ray.h"
#include "Object.h"
#include "Material.h"
#include <Eigen/Core>
#include <vector>
#include <memory>
#include <cmath>

// Find the first (visible) hit given a ray and a collection of scene objects
//
// Inputs:
//   ray  ray along which to search
//   min_t  minimum t value to consider (for viewing rays, this is typically at
//     least the _parametric_ distance of the image plane to the camera)
//   objects  list of objects (shapes) in the scene
// Outputs:
//   hit_id  index into objects of object with first hit
//   t  _parametric_ distance along ray so that ray.origin+t*ray.direction is
//     the hit location
//   n  surface normal at hit location
// Returns true iff a hit was found
bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  double & t,
  Eigen::Vector3d & hit_point,
  Eigen::Vector3d & n,
  std::shared_ptr<Material> & material,
  Eigen::Vector3d & kd,
  Eigen::Vector3d & ks,
  Eigen::Vector3d & km,
  double & p);

// simple wrapper around first_hit for checking shade
bool check_shade(
  const std::vector< std::shared_ptr<Object> > & objects,
  const Eigen::Vector3d & hit_point,
  const Eigen::Vector3d & direction,
  double min_t,
  double max_t  
) {
  Ray light_ray(hit_point, direction);
  double t, temp_p;
  Eigen::Vector3d temp_p, temp_n, temp_kd, temp_ks, temp_km;
  std::shared_ptr<Material> material;
  bool temp = first_hit(light_ray, min_t, objects, t, temp_p, temp_n, material, temp_kd, temp_ks, temp_km, temp_p);
  return temp && t <= max_t;
}

#endif
