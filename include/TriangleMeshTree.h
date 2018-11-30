#ifndef MESHTREE_H
#define MESHTREE_H

#include "BoundingBox.h"
#include "Object.h"
#include <Eigen/Core>
#include <memory>
#include <vector>

// Implementation
#include "ray_intersect_box.h"
#include "point_box_squared_distance.h"

struct TriangleMeshTree : public Object, public std::enable_shared_from_this<AABBTree>
{
  // Pointers to left and right subtree branches. These could be another
  // AABBTree (internal node) or a leaf (primitive Object like MeshTriangle, or
  // CloudPoint)
  BoundingBox box;
  std::shared_ptr<Object> left;
  std::shared_ptr<Object> right;
  // Construct a axis-aligned bounding box tree given a list of objects. Use the
  // midpoint along the longest axis of the box containing the given objects to
  // determine the left-right split.
  //
  // Inputs:
  //   objects  list of objects to store in this AABBTree
  //   Optional inputs:
  //     depth  depth of this tree (usually set by constructor of parent as
  //       their depth+1)
  // Side effects: num_leaves is set to objects.size() and left/right pointers
  // set to subtrees or leaf Objects accordingly.
  TriangleMeshTree(
    const std::vector<std::shared_ptr<Object> > & objects, 
    int depth=0);
  virtual bool intersect(
    const Ray & ray,
    const double min_t,
    Eigen::Vector3d & hit_p,
    Eigen::Vector3d & n,
    Eigen::Vector3d & kd,
    Eigen::Vector3d & ks,
    Eigen::Vector3d & km,
    double & p) const;
};

#endif
