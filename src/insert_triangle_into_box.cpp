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
  Eigen::Matrix<double, 4, 3> temp;
  temp.row(0) = a;
  temp.row(1) = b;
  temp.row(2) = c;
  temp.row(3) = B.min_corner;
  B.min_corner = temp.colwise().minCoeff();
  temp.row(3) = B.max_corner;
  B.max_corner = temp.colwise().maxCoeff();
  ////////////////////////////////////////////////////////////////////////////
}


