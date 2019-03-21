//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_SHADE_H
#define RAYMARCHER_SHADE_H

#include "Objects/Ray.h"
#include "Objects/Light.h"
#include "Objects/types.h"
#include "Objects/DirectionalLight.h"

Color shade(
        const Ray& ray,
        double (&sdf)(R3),
        const Lights& lights,
        const int hit_id,
        const R3& n,
        const double depth);

#endif //RAYMARCHER_SHADE_H
