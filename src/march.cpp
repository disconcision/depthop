//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "shade.h"

#include <iostream>

/* approximates normal at p*/
vec3 normal(double (&sdf)(vec3), const vec3& p) {
  double EPSILON = 1e-3;
  vec3 eu = vec3(EPSILON,0,0),
       ev = vec3(0,EPSILON,0),
       ew = vec3(0,0,EPSILON);
  return vec3(sdf(p + eu) - sdf(p - eu),
              sdf(p + ev) - sdf(p - ev),
              sdf(p + ew) - sdf(p - ew)).normalized();
}


Color march(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d) {

  double depth = min_d;
  unsigned MAX_STEPS = 80;
  double EPSILON = 1e-3;

  int hit_id; // todo: id for materials
  Color c = Color(0.0,0.0,0.0); // bkg color
  vec3 n; // normal at hit

  for (unsigned i=0; i < MAX_STEPS; i++) {
    vec3 p = ray.origin + depth*ray.direction;
    double d = sdf(p);
    if (d < EPSILON) {
      n = normal(sdf, p);
      return shade(ray, hit_id, n, depth);
    }
    depth += d;
    if (depth >= max_d) {
      return c;
    }
  }
  return c;
}
