//
// Created by disconcision on 21/03/19.
//

#include "sdf/primitives.h"

auto sphere (const R3 x) -> R {
  return x.norm() - 1.0;};

auto box (const R3 x) -> R {
  return (x.cwiseAbs() - R3(1,1,1)).maxCoeff();};

auto plane (const R3 x) -> R {
  return x.dot(R3(0,1,0));};

auto cylinder (const R3 x) -> R {
  return R2(x(0),x(2)).norm() - 1;};