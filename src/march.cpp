//
// Created by disconcision on 16/03/19.
//

#include "march.h"



vec3 normal(double (&sdf)(vec3), const vec3& p) {
  double EPSILON = 1e-15;
  vec3 ex = vec3(EPSILON,0,0),
       ey = vec3(0,EPSILON,0),
       ez = vec3(0,0,EPSILON);
  return vec3(sdf(p + ex) - sdf(p - ex),
              sdf(p + ey) - sdf(p - ey),
              sdf(p + ez) - sdf(p - ez)).normalized();
}


double march(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_t,
        const double max_t,
        int& hit_id,
        vec3& n) {

  double t = min_t;
  unsigned MAX_STEPS = 6;
  double EPSILON = 1e-10;

  for (unsigned i=0; i < MAX_STEPS; i++) {
    vec3 p = ray.origin + t*ray.direction;
    double d = sdf(p);
    if (d < EPSILON) {
      n = normal(sdf, p);
      return t;
    }
    t += d;
    if (t > max_t) {
      return max_t;
    }
  }
  return max_t;
}
