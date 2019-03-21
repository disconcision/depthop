//
// Created by disconcision on 16/03/19.
//

#include "screen.h"
#include "geometry.h"


R coordTransform(R x, R d_src, R d_target) {
  /* per-coordinate screenspace to cameraspace */
  return (d_src * (x + 0.5)/d_target) - d_src/2;
}

Ray screen(const Camera &camera, const Image &image,
           const unsigned i, const unsigned j) {
  /* returns a ray from the eye of the camera
   * through pixel (i,j) on the image screen */

  R3 rayDirectionInCameraspace(
          coordTransform(j, camera.width, image.width),
          coordTransform(image.height - i, camera.height, image.height),
          -camera.d);

  R3x3 cameraToWorld = R3x3_from_3xR3(camera.u, camera.v, camera.w);

  return Ray(camera.e, normalize(cameraToWorld*rayDirectionInCameraspace));
}
