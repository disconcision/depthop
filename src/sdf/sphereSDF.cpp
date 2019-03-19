//
// Created by disconcision on 16/03/19.
//

#include "sdf/sphereSDF.h"

double sphere_sdf(const vec3 p) {
  return p.norm() - 1.0;
}