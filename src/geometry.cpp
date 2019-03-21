//
// Created by disconcision on 20/03/19.
//

#include "geometry.h"
#include <Eigen/Geometry>


R mod(R x, R y) {
  return x - y*floor(x/y);
}

R3 modR3(R3 x, R3 y) {
  return R3(mod(x(0),y(0)),mod(x(1),y(1)),mod(x(2),y(2)));
}

R clamp(R x, R lo, R hi) {
  return min(hi, max(x, lo));
}

R3 clampR3(R3 x, R lo, R hi) {
  return R3(
          clamp(x(0), lo, hi),
          clamp(x(1), lo, hi),
          clamp(x(2), lo, hi));
}

double mix(R x, R y, R a) {
  return (1 - a)*x + a*y;
}

// todo:
// operator + on R2,R3,R4
// operator * on R2,R3,R4
// for shade.cpp:
//R3 cwise_mult(const R3& a, const R3& b) { return cMult(a,b); }

R3 normalize(const R3& x) { return x.normalized(); }
R dotR3(const R3& a, const R3& b) { return a.dot(b); }


R3x3 R3x3_from_3xR3 (R3 c0, R3 c1, R3 c2) {
  R3x3 M(3,3); // = R3x3_from_3xR3 (camera.u, camera.v, camera.w);
  M << c0, c1, c2;
  return M;
}

R3 follow(const Ray& ray, R depth) {
  /* follow a ray along a distance */
  return ray.origin + depth*ray.direction;
}