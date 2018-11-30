#include "insert_triangle_into_box.h"
#include <algorithm>

void insert_triangle_into_box(
  const Eigen::RowVector3d & a,
  const Eigen::RowVector3d & b,
  const Eigen::RowVector3d & c,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  for (int i = 0; i < 3; i++) {
    B.min_corner[i] = fmin(fmin(fmin(a[i], b[i]), c[i]), B.min_corner[i]);
    B.max_corner[i] = fmax(fmax(fmax(a[i], b[i]), c[i]), B.max_corner[i]);
  }
  ////////////////////////////////////////////////////////////////////////////
}


