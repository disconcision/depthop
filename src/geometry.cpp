//
// Created by disconcision on 20/03/19.
//

#include "geometry.h"
#include "constants.h"
#include <Eigen/Geometry>
//#include <cmath>
//#include<functional>


R3 normal(R (&sdf)(R3), const R3& p) {
  /* approximates the normal at a point p by
   * approximating the gradient of the sdf. */

  R3 eu = R3(EPSILON_NORMAL,0,0),
          ev = R3(0,EPSILON_NORMAL,0),
          ew = R3(0,0,EPSILON_NORMAL);

  return normalize(R3(
          sdf(p + eu) - sdf(p - eu),
          sdf(p + ev) - sdf(p - ev),
          sdf(p + ew) - sdf(p - ew)));
}


R3 follow(const Ray& ray, R depth) {
  /* follow a ray along a distance */
  return ray.origin + depth*ray.direction;
}


template<typename F>
auto map(F f, R2 x) -> R2 {
  return R2(f(x(0)), f(x(1)));};

template<typename F>
auto map(F f, R3 x) -> R3 {
  return R3(f(x(0)), f(x(1)), f(x(2)));};

R2 sin(R2 x) {
  auto f = [](R x){return sin(x);};
  return map(f, x);}

R fract(R x) { return x - floor(x); }
// todo: why do i need to declare this lambda?
auto fract_int = [](R x) -> R { return fract(x); };
R2 fract (const R2 x) { return map(fract_int, x);}
R3 fract (const R3 x) { return map(fract_int, x);}
// no apparent time diff for inlined versions
//R2 fract (const R2 x) { return R2(fract(x(0)),fract(x(1)));}
//R3 fract (const R3 x) { return R3(fract(x(0)),fract(x(1)),fract(x(2)));}


R smooth_step(R x) {
  if (x <= 0) return 0.0;
  if (x < 1) return ((6*x - 15)*x + 10)*x*x*x;
  return 1.0;
}


R3 smooth_step(R3 x) {
  return R3(smooth_step(x(0)),smooth_step(x(1)),smooth_step(x(2)));
  //auto f = [](R x) -> R {return smooth_step(x);};
  //return map(f, x);
}



R dot(R2 a, R2 b) { return a.dot(b); }
R dot(R3 a, R3 b) { return a.dot(b); }
R length (R2 x) { return x.norm(); }
R length (R3 x) { return x.norm(); }
R mod(R x, R y) { return x - y*floor(x/y); }
R3 mod(R3 x, R3 y) { return R3(mod(x(0),y(0)),mod(x(1),y(1)),mod(x(2),y(2)));}
R2 floor(R2 x) { return R2(floor(x(0)), floor(x(1))); }
R3 floor(R3 x) { return R3(floor(x(0)), floor(x(1)), floor(x(2))); }
R3 cMult(R3 a, R3 b) { return (a.array() * b.array()).matrix(); }

R3 normalize(const R3& x) { return x.normalized(); }

R mix(R x, R y, R a) { return (1 - a)*x + a*y; }
R clamp(R x, R lo, R hi) { return min(hi, max(x, lo)); }
R3 clamp(R3 x, R lo, R hi) {
  return R3(
          clamp(x(0), lo, hi),
          clamp(x(1), lo, hi),
          clamp(x(2), lo, hi));
}




// todo: refactor to change_basis
R3x3 R3x3_from_3xR3 (R3 c0, R3 c1, R3 c2) {
  R3x3 M(3,3); // = R3x3_from_3xR3 (camera.u, camera.v, camera.w);
  M << c0, c1, c2;
  return M;
}

// todo:
// operator + on R2,R3,R4
// operator * on R2,R3,R4



