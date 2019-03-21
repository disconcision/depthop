//
// Created by disconcision on 16/03/19.
//

#include "Objects/Ray.h"
#include "Objects/Camera.h"
#include "Objects/Image.h"
#include "Objects/Lights.h"

#include "screen.h"
#include "field.h"
#include "march.h"
#include "shade.h"
//#include "write.h"

#include <Eigen/Geometry>
#include <iostream>

#include <omp.h>


const R MIN_D = 0.0;
const R MAX_D =  200.0;


int main(int argc, char* argv[])
{

  /* IMAGE PLANE */

  unsigned width = (argc != 3) ?
          400 : (unsigned) strtol(argv[1], nullptr,0);
  unsigned height = (argc != 3) ?
          400 : (unsigned) strtol(argv[2], nullptr,0);
  Image image(width, height, 3);


  /* CAMERA */

  Camera camera;
  camera.d = 1.0;
  camera.e = R3(0,0,5);
  camera.v = R3(0,1,0);
  camera.w = -R3(0,0,-1);
  camera.u = camera.v.cross(camera.w);
  camera.height = 1.0;
  camera.width = width/(double)height;


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
   * a normal and a hit id. color the pixel based on
   * those values and set the pixel accordingly.
   *
   */
  #pragma omp parallel num_threads(6)
  #pragma omp for schedule(dynamic,1)
  for (unsigned i = 0; i < image.height; ++i) {
    for (unsigned j = 0; j < image.width; ++j) {
      Ray ray = screen(camera, i, j, image);
      unsigned hit;
      R3 normal;
      R depth = march(ray, field, MIN_D, MAX_D, normal, hit);
      Color c = shade(ray, field, lights, hit, normal, depth);
      image.set_pixel(i, j, c);
    }
  }
  image.to_file("scene.ppm");
}



/*
bool intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n){

  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = R3(0,0,0);// todo: hardcode
  double r = 1; // todo: hardcode

  // set up quadratic to solve for intersections
  double A = d.dot(d);
  double B = 2*d.dot(e) - 2*c.dot(d);
  double C = e.dot(e) - 2*c.dot(e) + c.dot(c) - r*r;

  double D = B*B-4*A*C;

  if(D < 0) {
    // no intersections
    return false;
  } else {

    // this case covers one or two intersections
    double r1 = (-B + sqrt(D))/(2*A);
    double r2 = (-B - sqrt(D))/(2*A);

    // we can't just return the closest intersection
    // as only the further one may be above the cutoff
    if (r1<=r2)
      t = (r1 >= min_t)?r1:r2;
    else
      t = (r2 >= min_t)?r2:r1;

    Eigen::Vector3d p = e + t*d;
    n = (p-c).normalized();

    return t >= min_t;
  }
}
*/

/*
double tt;
R3 nn;
if (intersect(ray, 1.0, tt, nn)) {
  //c = {0.8,0.3,0.2};
  c[0] = (nn(0)*0.5+0.5);
  c[1] = (nn(1)*0.5+0.5);
  c[2] = (nn(2)*0.5+0.5);
  set_pixel(image, i, j, c);
}
*/
