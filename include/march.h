//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_MARCH_H
#define RAYMARCHER_MARCH_H

#include "Ray.h"
#include "types.h"

double march(
        const Ray& ray,
        double (&f)(vec3),
        const double min_t,
        const double max_t,
        int& hit_id,
        vec3& n);

#endif //RAYMARCHER_MARCH_H
