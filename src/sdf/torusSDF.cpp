//
// Created by disconcision on 16/03/19.
//

#include "sdf/torusSDF.h"

double torus_sdf(const vec3 p) {
  vec2 t = vec2(1, 1.5);
  vec2 q = vec2((vec2(p(0),p(2))).norm() - t(0), p(1));
  return q.norm() - t(1);
}