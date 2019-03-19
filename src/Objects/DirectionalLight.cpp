//
// Created by disconcision on 16/03/19.
//

#include "Objects/DirectionalLight.h"

void DirectionalLight::direction(
        const vec3 &p, vec3 &d, double &max_t) const {
  // ignore query point
  d = - this->d.normalized();
  max_t = DBL_INFINITY;
}