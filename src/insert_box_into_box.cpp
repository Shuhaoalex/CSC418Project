#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  Eigen::Matrix<double, 2, 3> temp;
  temp.row(0) = A.max_corner;
  temp.row(1) = B.max_corner;
  B.max_corner = temp.colwise().maxCoeff();
  temp.row(0) = A.min_corner;
  temp.row(1) = B.min_corner;
  B.min_corner = temp.colwise().minCoeff();
  ////////////////////////////////////////////////////////////////////////////
}