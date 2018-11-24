#include <Eigen/Core>

Eigen::Vector3d reflect(const Eigen::Vector3d & in, const Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d along_n_comp = n * (n.dot(-1 * in));
  return (in + 2 * along_n_comp).normalized();
  ////////////////////////////////////////////////////////////////////////////
}
