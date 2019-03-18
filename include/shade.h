//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_SHADE_H
#define RAYMARCHER_SHADE_H

#include "Ray.h"
#include "Light.h"
#include "types.h"
#include "DirectionalLight.h"
#include <memory>

using Lights =  std::vector< std::shared_ptr<Light>>;

Color shade(
        const Ray &ray,
        const int hit_id,
        const vec3 &n,
        const double depth);

#endif //RAYMARCHER_SHADE_H
