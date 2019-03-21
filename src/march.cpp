//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "shade.h"
#include "geometry.h"

const R EPSILON_NORMAL = 1e-3;
const unsigned MARCH_MAX_STEPS = 180;
const R EPSILON_MARCH = 1e-5;

R3 normal(R (&sdf)(R3), const R3& p) {
  /* approximates the normal at a point p by
   * approximating the gradient of the sdf. */

  const R EPS = EPSILON_NORMAL;
  R3 eu = R3(EPS,0,0),
     ev = R3(0,EPS,0),
     ew = R3(0,0,EPS);

  return normalize(R3(
          sdf(p + eu) - sdf(p - eu),
          sdf(p + ev) - sdf(p - ev),
          sdf(p + ew) - sdf(p - ew)));
}


R march(const Ray& ray, R (&sdf)(R3),
        const R min_d, const R max_d,
        R3& n, unsigned& hit_id) {
  /* march along a ray towards towards the sdf
   * starting at depth min_d and returning the
   * depth to level set surface, up to max_d */

  R depth = min_d;

  for (unsigned i=0; i < MARCH_MAX_STEPS; i++) {
    R3 point = follow(ray, depth);
    R distance = sdf(point);
    if (distance < EPSILON_MARCH) {
      n = normal(sdf, point);
      return depth;
    }
    depth += distance;
    if (depth >= max_d) break;
  }
  return depth;
}

