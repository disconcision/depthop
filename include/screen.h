//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_VIEWING_RAY_H
#define RAYMARCHER_VIEWING_RAY_H

#include "Objects/types.h"
#include "Objects/Ray.h"
#include "Objects/Camera.h"
#include "Objects/Image.h"


/* returns a ray from the eye of the camera
 * through pixel (i,j) on the image screen */
Ray screen(const Camera &camera, const Image &image,
           const unsigned i, const unsigned j);


#endif //RAYMARCHER_VIEWING_RAY_H
