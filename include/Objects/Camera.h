//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_CAMERA_H
#define RAYMARCHER_CAMERA_H

#include <Eigen/Core>
#include "types.h"

struct Camera {
  vec3 e; // eye
  vec3 u,v,w; // v is up, -w is view direction, u = vxw
  double d; // distance to focal plane
  double width, height; // image plane
};

#endif //RAYMARCHER_CAMERA_H
