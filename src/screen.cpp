//
// Created by disconcision on 16/03/19.
//

#include "screen.h"
#include "geometry.h"

Ray screen_to_world(const Camera &camera, const Image &image,
                    const unsigned i, const unsigned j) {
  /* returns a ray from the eye of the camera
   * through pixel (i,j) on the image screen */
  return Ray(camera.e, normalize(
          /* transformation from cameraspace to worldspace */
          R3x3_from_3xR3(camera.u, camera.v, camera.w) *
          /* transformation from screenspace to cameraspace*/
          R3(camera.width * ((j + 0.5)/image.width - 0.5),
             camera.height * ((image.height - i + 0.5)/image.height - 0.5),
             -camera.d)));
}
