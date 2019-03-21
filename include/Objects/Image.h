//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_IMAGE_H
#define RAYMARCHER_IMAGE_H

#include "types.h"
#include <vector>
#include <fstream>
#include <iterator>


struct Image {

    std::vector<unsigned char> data;
    unsigned num_channels = 3;
    unsigned width, height;

    Image(unsigned w, unsigned h) {
      this->width = w;
      this->height = h;
      this->num_channels = 3;
      this->data = std::vector<unsigned char>(3*w*h);
    }


    void set_pixel(unsigned i, unsigned j, Color color) {
      /* set pixel (i,j) to color, which is converted from
       * a double in [0.0, 1.0] to an integer in [0, 255]*/
      for (unsigned c=0; c < this->num_channels; c++) {
        this->data[c + this->num_channels*(j + i*this->width)]
                = (unsigned char) (255*color(c));
      }
    }


    bool to_file(const std::string &filename) {
      /* write image data to a PPM file */
      std::ofstream f;
      f.open(filename);
      if (!f) return false;

      std::string code;
      if (this->num_channels == 1)
        code = "P2\n";
      else
        code = "P3\n";

      f << code << "\n" << this->width << " "
        << this->height << "\n" << 255 << "\n";

      std::copy(this->data.begin(), this->data.end(),
                std::ostream_iterator<int>(f, " "));

      f.close();
      return true;
    }
};


#endif //RAYMARCHER_IMAGE_H
