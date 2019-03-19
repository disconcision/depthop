//
// Created by disconcision on 16/03/19.
//

#include "sdf/boxSDF.h"
#include "Objects/types.h"

double box_sdf(const vec3 p) {
  // vector of distance along each dimension
  vec3 dist = p.cwiseAbs() - vec3(0.07,0.5,3.0); //size
  //double r = 1.0;
  //double m = std::max(0.0, dist.norm());
  return dist.maxCoeff(); // + std::min(0.0, dist.maxCoeff());
}
