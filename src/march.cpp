//
// Created by disconcision on 16/03/19.
//

#include "march.h"
#include "shade.h"

#include <iostream>

/* approximates normal at p*/
vec3 normal(double (&sdf)(vec3), const vec3& p) {
  /* approximates the normal at a point p by
   * approximating the gradient of the sdf.
   */
  double EPSILON = 1e-3;
  vec3 eu = vec3(EPSILON,0,0),
       ev = vec3(0,EPSILON,0),
       ew = vec3(0,0,EPSILON);
  return vec3(sdf(p + eu) - sdf(p - eu),
              sdf(p + ev) - sdf(p - ev),
              sdf(p + ew) - sdf(p - ew)).normalized();
}


double march_internal(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d,
        vec3& n,
        int hit_id) {

  double depth = min_d;
  unsigned MAX_STEPS = 160;
  double EPSILON = 1e-5;

  for (unsigned i=0; i < MAX_STEPS; i++) {
    vec3 p = ray.origin + depth*ray.direction;
    double d = sdf(p);
    if (d < EPSILON) {
      n = normal(sdf, p);
      return depth;
    }
    depth += d;
    if (depth >= max_d) break;
  }
  return max_d;
}

Color march(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d) {

  int hit_id = 0; // todo: id for materials
  vec3 n; // normal at hit

  double depth =
          march_internal(ray,sdf,min_d,max_d,n,hit_id);

  if (depth >= max_d)
    return Color(0,0,0); // bkg color
  else
    return shade(ray, sdf, hit_id, n, depth);
  // quick color:
  // Color(1,1,1)*depth/200.0

}

