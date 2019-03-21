//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_VIEWING_RAY_H
#define RAYMARCHER_VIEWING_RAY_H

#include "Objects/types.h"
#include "Objects/Ray.h"
#include "Objects/Camera.h"
#include "Objects/Image.h"

Ray screen(
        const Camera &camera,
        const int i,
        const int j,
        Image &image);

#endif //RAYMARCHER_VIEWING_RAY_H
