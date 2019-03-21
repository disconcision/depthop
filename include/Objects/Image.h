//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_IMAGE_H
#define RAYMARCHER_IMAGE_H

#include "types.h"
#include <vector>

struct Image {

    std::vector<unsigned char> data;
    unsigned num_channels = 3;
    unsigned width, height;

    Image(unsigned w, unsigned h, unsigned n_c) {
      this->num_channels = n_c;
      this->width = w;
      this->height = h;
      this->data = std::vector<unsigned char>(n_c*w*h);
    }

    void set_pixel(unsigned i, unsigned j, Color color) {
      for (unsigned c=0; c < this->num_channels; c++) {
        this->data[c + this->num_channels*(j + i*this->width)]
                = (unsigned char) (255*color(c));
      }
    }
};

#endif //RAYMARCHER_IMAGE_H
