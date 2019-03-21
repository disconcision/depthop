//
// Created by disconcision on 16/03/19.
//

#include "Objects/DirectionalLight.h"

void DirectionalLight::direction(
        const R3& p,
        R3& d,
        double& max_d) const {
  // ignore query point
  d = - this->d.normalized();
  max_d = DBL_INFINITY;
}