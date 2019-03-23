//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_SHADE_H
#define RAYMARCHER_SHADE_H

#include "Objects/types.h"
#include "Objects/Ray.h"
#include "Objects/Lights.h"

Color shade(
        const Ray& ray,
        R (&sdf)(R3),
        const Lights& lights,
        const R depth,
        unsigned& steps,
        const unsigned hit_id);

#endif //RAYMARCHER_SHADE_H
