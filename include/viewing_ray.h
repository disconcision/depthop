//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_VIEWING_RAY_H
#define RAYMARCHER_VIEWING_RAY_H

#include "Ray.h"
#include "Camera.h"
#include "Image.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  Image image,
  Ray & ray);

#endif //RAYMARCHER_VIEWING_RAY_H
