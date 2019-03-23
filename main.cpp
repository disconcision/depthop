//
// Created by disconcision on 16/03/19.
//

#include "Objects/Ray.h"
#include "Objects/Camera.h"
#include "Objects/Image.h"
#include "Objects/Lights.h"

#include "constants.h"

#include "screen.h"
#include "field.h"
#include "march.h"
#include "shade.h"

#include <omp.h>



int main(int argc, char* argv[]) {

  /* IMAGE PLANE */

  unsigned width = (argc != 3) ? DEFAULT_WIDTH :
          (unsigned) strtol(argv[1], nullptr,0);
  unsigned height = (argc != 3) ? DEFAULT_HEIGHT :
          (unsigned) strtol(argv[2], nullptr,0);
  Image image(width, height);


  /* CAMERA */

  Camera camera(
          1.0,                  // focal distance
          1.0,                  // frame width
          width/(double)height, // frame height
          R3(0,0,5),            // eye position
          R3(0,0,-1),           // view direction
          R3(0,1,0));           // up direction


  /* LIGHTS */

  Lights lights;
  lights.add_directional(
          R3(-1,-1,-1),
          Color(0.8,0.8,0.8),
          true);
  lights.add_directional(
          R3(-0, 1, 0),
          Color(0.0,0.3,0.8),
          false);

  /*
   * for each pixel (i,j) in the image plane,
   * take a ray from the camera through that pixel,
   * and march along that ray, returning a depth and
   * a number of steps and a hit id.
   * color the pixel based on those values.
   *
   */
  #pragma omp parallel num_threads(NUM_THREADS)
  #pragma omp for schedule(dynamic,1)
  for (unsigned i = 0; i < image.height; ++i) {
    for (unsigned j = 0; j < image.width; ++j) {
      Ray ray = screen(camera, image, i, j);
      unsigned hit, steps;
      R3 normal;
      R depth = march(ray, field, steps, hit);
      Color c = shade(ray, field, lights, depth, steps, hit);
      image.set_pixel(i, j, c);
    }
  }
  image.to_file(FILENAME);
}
