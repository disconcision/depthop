//
// Created by disconcision on 16/03/19.
//

#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "viewing_ray.h"
#include "march.h"
#include "write_file.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>


void set_pixel(Image &image, unsigned i, unsigned j, Color color) {
  for (unsigned c=0; c < image.num_channels; c++) {
    image.data[c+3*(j+image.width*i)] = color[c];
  }
}


int main(int argc, char* argv[])
{

  // set up camera
  Camera camera;
  camera.d = 3;
  camera.e = vec3(0,0,5);
  camera.v = vec3(0,1,0);
  camera.w = -vec3(0,0,-1);
  camera.u = camera.v.cross(camera.w);
  camera.width = 1.0;
  camera.height = 1.0;

  // set up output image
  Image image;
  image.width = 400;
  image.height = 400;
  image.num_channels = 3;
  image.data = std::vector<unsigned char>(3*image.width*image.height);

  for(unsigned i=0; i<image.height; ++i) {
    for(unsigned j=0; j<image.width; ++j) {

      Ray ray;
      viewing_ray(camera, i, j, image, ray);
      double t;
      vec3 n;
      int hit_id;

      //std::cout << "march: " << march(ray, 0.0, 100.0, hit_id, n) <<"\n";

      if(-1 != march(ray, 0.0, 100.0, hit_id, n)) {
        //std::cout << "hit!\n";
        set_pixel(image, i, j, {190,80,70});
      } else {
        set_pixel(image, i, j, {0,0,0});
      }
    }
  }
  write_file("scene.ppm", image);
}
