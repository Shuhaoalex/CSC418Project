#include "AABBTree.h"
#include "insert_box_into_box.h"
#include <algorithm>

AABBTree::AABBTree(
  const std::vector<std::shared_ptr<Object> > & objects,
  int a_depth): 
  depth(std::move(a_depth)), 
  num_leaves(objects.size())
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  this->box = BoundingBox(objects[0]->box.min_corner, objects[0]->box.max_corner);
  for (int i = 1; i < objects.size(); i++) {
    insert_box_into_box(objects[i]->box, this->box);
  }

  if (objects.size() == 2) {
    this->left = objects[0];
    this->right = objects[1];
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
      this->left = std::make_shared<AABBTree>(left_objects, this->depth + 1);
    }

    if (right_objects.size() >= 2){
      this->right = std::make_shared<AABBTree>(right_objects, this->depth + 1);
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}

bool AABBTree::intersect(
  const Ray& ray,
  const double min_t,
  HitInfo & hit_info) const 
{
  ////////////////////////////////////////////////////////////////////////////
  if (!ray_intersect_box(ray, this->box, min_t)) {
    return false;
  }
  HitInfo l_info, r_info;
  bool hit_left = this->left->intersect(ray, min_t, l_info);
  bool hit_right = this->right->intersect(ray, min_t, r_info);

  if (hit_left && hit_right) {
    if(l_info.t <= r_info.t){
      hit_info = l_info;
    } else {
      hit_info = r_info;
    }
    return true;
  } else if (hit_left) {
    hit_info = l_info;
    return true;
  } else if (hit_right){
    hit_info = r_info;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}