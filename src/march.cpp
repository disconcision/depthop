//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "shade.h"
#include "geometry.h"
#include "constants.h"



R march(const Ray& ray, R (&sdf)(R3),
        const R min_d, const R max_d,
        unsigned& steps, unsigned& hit_id) {
  /* march along a ray towards towards the sdf
   * starting at depth min_d and returning the
   * depth to level set surface, up to max_d */

  R depth = min_d;

  for (steps=0; steps < MARCH_MAX_STEPS; steps++) {
    R3 point = follow(ray, depth);
    R distance = sdf(point);
    if (distance < EPSILON_MARCH) {

      return depth;
    }
    depth += distance;
    if (depth >= max_d) break;
  }
  return depth;
}

