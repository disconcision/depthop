//
// Created by disconcision on 19/03/19.
//

#include "sdf/rigid.h"


/* translates SDF through displacement d */
auto move (R3 d, SDF f) -> SDF {
  return [f, d] (R3 x) {
      return f(x - d);};}


/* affine-transforms SDF f according to the
 * INVERSE of the provided transformation */
auto affine (R4x4 T_inv, SDF f) -> SDF {
    return [f, T_inv] (R3 x) {
        R4 t = T_inv*R4(x(0),x(1),x(2),1);
        return f(R3(t(0),t(1),t(2)));};};


/* rotate SDF f about the x-axis
 * through an angle of a radians */
auto rotate_x (R a, SDF f) -> SDF {
    R c = cos(-a), s = sin(-a);
    R4x4 T;
    T <<
    1,  0,  0,  0,
    0,  c, -s,  0,
    0,  s,  c,  0,
    0,  0,  0,  1;
    return affine(T, f);};


/* rotate SDF f about the y-axis
 * through an angle of a radians */
auto rotate_y (R a, SDF f) -> SDF {
    R c = cos(-a), s = sin(-a);
    R4x4 T;
    T <<
     c,  0,  s,  0,
     0,  1,  0,  0,
    -s,  0,  c,  0,
     0,  0,  0,  1;
    return affine(T, f);};


/* rotate SDF f about the z-axis
 * through an angle of a radians */
auto rotate_z (R a, SDF f)  -> SDF {
    R c = cos(-a), s = sin(-a);
    R4x4 T;
    T <<
    c, -s,  0,  0,
    s,  c,  0,  0,
    0,  0,  1,  0,
    0,  0,  0,  1;
    return affine(T, f);};
