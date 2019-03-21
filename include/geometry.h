//
// Created by disconcision on 20/03/19.
//

#ifndef RAYMARCHER_GEOMETRY_H
#define RAYMARCHER_GEOMETRY_H

#include "Objects/types.h"
#include "Objects/Ray.h"

R3 follow(const Ray& ray, R depth);
R3 normalize(const R3& x);
R dotR3(const R3 &a, const R3 &b);
R3 cwise_mult(const R3 &a, const R3 &b);

double mod(double x, double y);

R3 modR3(R3 x, R3 y);

R clamp(R x, R lo, R hi);
R3 clampR3(R3 x, R lo, R hi);

R mix(R x, R y, R a);

R3x3 R3x3_from_3xR3 (R3 c0, R3 c1, R3 c2);

#endif //RAYMARCHER_GEOMETRY_H
