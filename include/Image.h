//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_IMAGE_H
#define RAYMARCHER_IMAGE_H

#include <vector>

struct Image {
    std::vector<unsigned char> data;
    int num_channels = 3;
    int width, height; // image size
};

#endif //RAYMARCHER_IMAGE_H
