//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_WRITE_FILE_H
#define RAYMARCHER_WRITE_FILE_H

#include "Image.h"
#include <vector>
#include <string>

bool write(
        const std::string &filename,
        Image &image);

#endif //RAYMARCHER_WRITE_FILE_H
