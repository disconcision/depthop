//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_MARCH_H
#define RAYMARCHER_MARCH_H

#include "Objects/Ray.h"
#include "Objects/types.h"

Color march(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d);

#endif //RAYMARCHER_MARCH_H
