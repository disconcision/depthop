//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_MARCH_H
#define RAYMARCHER_MARCH_H

#include "Objects/Ray.h"
#include "Objects/types.h"

R march(
        const Ray& ray,
        R (&sdf)(R3),
        double min_d,
        double max_d,
        R3& n,
        unsigned& hit_id);

#endif //RAYMARCHER_MARCH_H