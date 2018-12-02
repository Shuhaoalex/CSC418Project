#include "TriangleMeshTree.h"
#include "insert_box_into_box.h"
#include <algorithm>

TriangleMeshTree::TriangleMeshTree(
  const std::vector<std::shared_ptr<MeshTriangle> > & triangles,
  int a_depth)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  this->box = BoundingBox(triangles[0]->box.min_corner, triangles[0]->box.max_corner);
  for (int i = 1; i < triangles.size(); i++) {
    insert_box_into_box(triangles[i]->box, this->box);
  }

  if (triangles.size() == 2) {
    this->left = triangles[0];
    this->right = triangles[1];
  } else {
    int longest_axis;
    double axis_midpoint, axis_length;
    double length = 0;
    for (int i = 0; i < 3; i++) {
      axis_length = this->box.max_corner[i] - this->box.min_corner[i];
      if (axis_length > length) {
        length = axis_length;
        axis_midpoint = (this->box.max_corner[i] + this->box.min_corner[i])/2;
        longest_axis = i;
      }
    }

    std::vector<std::shared_ptr<Object>> left_objects, right_objects;
    for (int i = 0; i < objects.size(); i++) {
      if (objects[i]->box.center()[longest_axis] <= axis_midpoint) {
        left_objects.push_back(objects[i]);
      } else {
        right_objects.push_back(objects[i]);
      }
    }

    if (left_objects.size() == 0) {
      this->left = right_objects.back();
      right_objects.pop_back();
    } else if (right_objects.size() == 0) {
      this->right = left_objects.back();
      left_objects.pop_back();
    }
    
    if (left_objects.size() == 1){
      this->left = left_objects[0];
    }

    if (right_objects.size() == 1){
      this->right = right_objects[0];
    }
    
    if (left_objects.size() >= 2){
      this->left = std::make_shared<TriangleMeshTree>(left_objects);
    }

    if (right_objects.size() >= 2){
      this->right = std::make_shared<TriangleMeshTree>(right_objects);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool MeshTree::intersect(
  const Ray& ray,
  const double min_t,
  double & t,
  Eigen::Vector3d & hit_p,
  Eigen::Vector3d & n,
  std::shared_ptr<Material> & material,
  Eigen::Vector3d & kd,
  Eigen::Vector3d & ks,
  Eigen::Vector3d & km,
  double & p)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (!ray_intersect_box(ray, this->box, min_t)) {
    return false;
  }
  double r_t, l_t, l_p, r_p;
  std::shared_ptr<Material> l_mat, r_mat;
  Eigen::Vector3d l_hp, r_hp, l_n, r_n, l_kd, r_kd, l_ks, r_ks, l_km, r_km;

  bool hit_left = this->left->intersect(ray, min_t, l_t, l_hp, l_n, l_mat, l_kd, l_ks, l_km, l_p);
  bool hit_right = this->right->intersect(ray, min_t, r_t, r_hp, r_n, r_mat, r_kd, r_ks, r_km, r_p);
  if (hit_left && hit_right) {
    if (l_t <= r_t) {
      t = l_t;
      hit_p = l_hp;
      n = l_n;
      material = l_mat;
      kd = l_kd;
      ks = l_ks;
      km = l_km;
      p = l_p;
      return true;
    } else {
      t = r_t;
      hit_p = r_hp;
      n = r_n;
      material = r_mat;
      kd = r_kd;
      ks = r_ks;
      km = r_km;
      p = r_p;
      return true;
    }
  } else if (hit_left) {
    t = l_t;
    hit_p = l_hp;
    n = l_n;
    material = l_mat;
    kd = l_kd;
    ks = l_ks;
    km = l_km;
    p = l_p;
    return true;
  } else if (hit_right) {
    t = r_t;
    hit_p = r_hp;
    n = r_n;
    material = r_mat;
    kd = r_kd;
    ks = r_ks;
    km = r_km;
    p = r_p;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}