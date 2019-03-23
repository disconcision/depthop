//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "shade.h"
#include "geometry.h"
#include "constants.h"



R march(const Ray& ray, R (&sdf)(R3),
        unsigned& steps, unsigned& hit_id) {
  /* march along a ray towards towards the sdf
   * starting at depth min_d and returning the
   * depth to level set surface, up to max_d */

  R depth = MIN_D;

  for (steps=0; steps < MARCH_MAX_STEPS; steps++) {
    R3 point = follow(ray, depth);
    R distance = sdf(point);
    if (distance < EPSILON_MARCH) {

      return depth;
    }
    depth += distance;
    if (depth >= MAX_D) break;
  }
  return depth;
}

