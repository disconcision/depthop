//
// Created by disconcision on 16/03/19.
//

#include "boxSDF.h"
#include "types.h"

double box_sdf(const vec3 p) {
  vec3 dist = p.cwiseAbs() - vec3(2,0.5,2); //size
  double m = std::max(0.0, dist.norm());
  return m + std::min(0.0, dist.maxCoeff());
}
