//
// Created by disconcision on 16/03/19.
//

#include "Objects/Ray.h"
#include "Objects/Camera.h"
#include "Objects/Image.h"

#include "screen.h"
#include "field.h"
#include "march.h"
#include "shade.h"
#include "write.h"

#include "sdf/sphereSDF.h"
#include "sdf/boxSDF.h"
#include "sdf/torusSDF.h"
#include "sdf/cylinderSDF.h"

#include <Eigen/Geometry>
#include <iostream>


void set_pixel(Image &image, unsigned i, unsigned j, Color color) {

  for (unsigned c=0; c < image.num_channels; c++) {
    image.data[c + image.num_channels*(j + i*image.width)]
      = (unsigned char) (255*color(c));
  }
}


bool intersect(
        const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n)
{

  Eigen::Vector3d d = ray.direction;
  Eigen::Vector3d e = ray.origin;
  Eigen::Vector3d c = vec3(0,0,0);// todo: hardcode
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

int main(int argc, char* argv[])
{

  // set up camera
  Camera camera;
  camera.d = 1.0;
  camera.e = vec3(0,0,5);
  camera.v = vec3(0,1,0);
  camera.w = -vec3(0,0,-1);
  camera.u = camera.v.cross(camera.w);
  camera.width = 1.0;
  camera.height = 1.0;

  // set up output image
  Image image;
  image.width = 800;
  image.height = 800;
  image.num_channels = 3;
  image.data = std::vector<unsigned char>(image.num_channels*image.width*image.height);

  for(unsigned i=0; i < image.height; ++i) {
    for(unsigned j=0; j < image.width; ++j) {

      // get a ray from camera eye through screen pixel (i,j)
      Ray ray = screen(camera, i, j, image);

      int hit_id; // todo: id for materials
      Color c = Color(0.0,0.0,0.0); // bkg color
      vec3 n; // normal at hit

      double min_d = 0.0, max_d = 100.0,
             depth = march(ray, field, min_d, max_d, hit_id, n);

      if(depth < max_d) {
        c = shade(ray, hit_id, n, depth);
      }

      set_pixel(image, i, j, c);

      /*
      double tt;
      vec3 nn;
      if (intersect(ray, 1.0, tt, nn)) {
        //c = {0.8,0.3,0.2};
        c[0] = (nn(0)*0.5+0.5);
        c[1] = (nn(1)*0.5+0.5);
        c[2] = (nn(2)*0.5+0.5);
        set_pixel(image, i, j, c);
      }
      */
    }
  }
  write("scene.ppm", image);
}
