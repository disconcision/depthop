//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_CAMERA_H
#define RAYMARCHER_CAMERA_H

#include "types.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

struct Camera {

  R3 e;
  R3 u,v,w;
  double d;
  double width, height;

  Camera(R d, R h, R w, R3 e, R3 view, R3 up) {
    this->d = d;
    this->e = e;
    this->w = -view;
    this->v = up;
    this->u = (this->v).cross(this->w);
    this->height = h;
    this->width = w;
  }

};

#endif //RAYMARCHER_CAMERA_H
