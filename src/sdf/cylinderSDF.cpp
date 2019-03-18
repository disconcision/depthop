//
// Created by disconcision on 16/03/19.
//

#include "cylinderSDF.h"

double cylinder_sdf(const vec3 p) {
  vec3 c = vec3(0.5, 0.3, 0.6);
  return (vec2(p(0) - c(0),p(2) - c(1))).norm() - c(3);
}