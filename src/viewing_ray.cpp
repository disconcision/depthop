//
// Created by disconcision on 16/03/19.
//

#include "viewing_ray.h"
#include <iostream>

/* transforms a single coordinate from screenspace to cameraspace */
double coordTransform(double i, double d_src, double d_target) {
    return (d_src * (i + 0.5)/d_target) - d_src/2;
}

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  Image image,
  Ray & ray)
{
  // cameraspace direction of ray
  Eigen::Vector3d rayDirectionInCameraspace(
          coordTransform(j, camera.width, image.width),
          coordTransform(image.height - i, camera.height, image.height),
          -camera.d);

  // camera to worldspace transformation matrix
  Eigen::MatrixXd cameraToWorld(3,3);
  cameraToWorld << camera.u, camera.v, camera.w;

  ray.origin = camera.e;
  ray.direction = (cameraToWorld*rayDirectionInCameraspace).normalized();
}
