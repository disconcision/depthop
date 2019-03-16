//
// Created by disconcision on 16/03/19.
//

#include "sphereSDF.h"

using vec3 = Eigen::Vector3d;

double sphere_sdf(const vec3 p) {
  return p.norm() - 2.0;
}