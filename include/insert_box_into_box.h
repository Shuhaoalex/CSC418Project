#ifndef INSERT_BOX_INTO_BOX_H
#define INSERT_BOX_INTO_BOX_H
#include "BoundingBox.h"
#include <Eigen/Core>
// Grow a box `B` by inserting a box `A`.
//
// Inputs:
//   A  bounding box to be inserted
//   B  bounding box to be grown
// Outputs:
//   B  bounding box grown to include original contents and A
void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B) {
    for (int i = 0; i < 3; i++) {
      B.min_corner[i] = fmin(B.min_corner[i], A.min_corner[i]);
      B.max_corner[i] = fmax(B.max_corner[i], A.max_corner[i]);
    }
  }
#endif
