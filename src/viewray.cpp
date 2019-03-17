//
// Created by disconcision on 16/03/19.
//

#include "viewray.h"
#include <iostream>

/* transforms a single coordinate from screenspace to cameraspace */
double coordTransform(double i, double d_src, double d_target) {
    return (d_src * (i + 0.5)/d_target) - d_src/2;
}

Ray viewray(const Camera &camera,
        const int i, const int j,
        Image &image)
{
  // cameraspace direction of ray
  vec3 rayDirectionInCameraspace(
          coordTransform(j, camera.width, image.width),
          coordTransform(image.height - i, camera.height, image.height),
          -camera.d);

  // camera to worldspace transformation matrix
  Eigen::Matrix3d cameraToWorld(3,3);
  cameraToWorld << camera.u, camera.v, camera.w;

  Ray ray;
  ray.origin = camera.e;
  ray.direction = (cameraToWorld*rayDirectionInCameraspace).normalized();

  return ray;
}
