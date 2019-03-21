//
// Created by disconcision on 21/03/19.
//

#include "sdf/primitive.h"

auto sphere (const R3 x) -> R {
  /* unit sphere at origin */
  return x.norm() - 1;}

auto box (const R3 x) -> R {
  /* unit cube at origin */
  return (x.cwiseAbs() - R3(1,1,1)).maxCoeff();}

auto plane (const R3 x) -> R {
  /* upward-facing flat y-axis plane at origin */
  return x.dot(R3(0,1,0));}

auto cylinder (const R3 x) -> R {
  /* infinite unit y-axis cylinder at origin */
  return R2(x(0),x(2)).norm() - 1;}