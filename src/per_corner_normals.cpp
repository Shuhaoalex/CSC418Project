#include "per_corner_normals.h"
#include "triangle_area_normal.h"
#include "vertex_triangle_adjacency.h"
#include <iostream>
#include <cmath>
#include <assert.h>

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  double pi = 3.1415926535897932384626;
  double radian = (corner_threshold/180.0) * pi;
  double corner_threshold_cosine = cos(radian);
  N.resize(F.rows() * 3, 3);
  std::vector<std::vector<int>> VF;
  vertex_triangle_adjacency(F, V.rows(), VF);
  Eigen::MatrixXd FaceNormals(F.rows(), 3);
  for (int i = 0; i < F.rows(); ++i) {
    FaceNormals.row(i) << triangle_area_normal(V.row(F(i,0)),V.row(F(i,1)),V.row(F(i,2)));
  }
  
  for (int i = 0; i < F.rows(); ++i) {
    Eigen::RowVector3d curr_face_normal = FaceNormals.row(i).normalized();
    int begin_point = i * 3;
    for (int j = 0; j < 3; ++j) {
      int v = F(i, j);
      Eigen::RowVector3d normal = Eigen::RowVector3d::Zero();
      for (int k = 0; k < VF[v].size(); ++k) {
        int f = VF[v][k];
        Eigen::RowVector3d temp = FaceNormals.row(f).normalized();
        if (temp.dot(curr_face_normal) >= corner_threshold_cosine) {
          normal += FaceNormals.row(f);
        }
      }
      N.row(begin_point + j) << normal.normalized();
    }
  }
  ////////////////////////////////////////////////////////////////////////////
}