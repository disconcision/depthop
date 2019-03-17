//
// Created by disconcision on 16/03/19.
//

#include "Ray.h"
#include "Camera.h"
#include "Image.h"
#include "viewray.h"
#include "lightray.h"
#include "march.h"
#include "write_file.h"
#include "sphereSDF.h"
#include "boxSDF.h"
#include "torusSDF.h"
#include "cylinderSDF.h"

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <vector>
#include <iostream>


void set_pixel(Image &image, unsigned i, unsigned j, Color color) {

  for (unsigned c=0; c < image.num_channels; c++) {
    image.data[c+image.num_channels*(j+image.width*i)]
      = (unsigned char) (255*color(c));
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
  image.data = std::vector<unsigned char>(image.num_channels*image.width*image.height);

  for(unsigned i=0; i<image.height; ++i) {
    for(unsigned j=0; j<image.width; ++j) {
      Ray ray = viewray(camera, i, j, image);
      double t;
      int hit_id;
      Color c;
      vec3 n;

      //std::cout << "march: " << march(ray, 0.0, 100.0, hit_id, n) <<"\n";
      double min_d = 3.0, max_d = 100.0,
             depth = march(ray, sphere_sdf, min_d, max_d, hit_id, n);
      if(depth < max_d) {
        //c = {0.8,0.3,0.2};
        //c[0] = (n(0)*0.5+0.5);
        //c[1] = (n(1)*0.5+0.5);
        //c[2] = (n(2)*0.5+0.5);
        c = lightray(ray, hit_id, n, depth);
      } else {
        c = Color(0.0,0.0,0.0);
      }
      set_pixel(image, i, j, c);
    }
  }
  write_file("scene.ppm", image);
}
