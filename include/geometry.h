//
// Created by disconcision on 20/03/19.
//

#ifndef RAYMARCHER_GEOMETRY_H
#define RAYMARCHER_GEOMETRY_H

#include "Objects/types.h"
#include "Objects/Ray.h"


R3 normal(R (&sdf)(R3), const R3& p);

R3 follow(const Ray& ray, R depth);

R fract(R x);
R2 fract(R2 x);
R3 fract(R3 x);
R2 floor(R2 x);
R3 floor(R3 x);
R dot(R2 a, R2 b);
R dot(R3 a, R3 b);
R length (R2 x);
R length (R3 x);
R mod(R x, R y);
R3 mod(R3 x, R3 y);
R clamp(R x, R lo, R hi);
R3 clamp(R3 x, R lo, R hi);
R2 sin (R2 x);
R3 normalize(const R3& x);
R mix(R x, R y, R a);
R3 cMult(R3 a, R3 b);
R smooth_step(R x);
R3 smooth_step(R3 x);
R3x3 R3x3_from_3xR3 (R3 c0, R3 c1, R3 c2);


#endif //RAYMARCHER_GEOMETRY_H
