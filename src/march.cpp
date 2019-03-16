//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "sphereSDF.h"


double march(
        const Ray & ray,
        const double min_t,
        const double max_t,
        int& hit_id,
        vec3& n) {

  double t = min_t;
  unsigned MAX_STEPS = 12;
  unsigned EPSILON = 0.001;

  for (unsigned i=0; i < MAX_STEPS; i++) {
    double d = sphere_sdf(ray.origin + t*ray.direction);
    if (d < EPSILON) {
      return t;
    }
    t += d;
    if (t > max_t) {
      return -1; // todo: ??
    }
  }
  return -1; // todo: ??
}
