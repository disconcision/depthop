//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_DIRECTIONALLIGHT_H
#define RAYMARCHER_DIRECTIONALLIGHT_H

#include "Light.h"
#include "types.h"

class DirectionalLight : public Light {

public:
    vec3 d; // light-to-scene direction
    void direction(
            const vec3& p,
            vec3& d,
            double& max_t
    ) const;
};

#endif //RAYMARCHER_DIRECTIONALLIGHT_H
