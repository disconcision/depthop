//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_DIRECTIONALLIGHT_H
#define RAYMARCHER_DIRECTIONALLIGHT_H

#include "Light.h"
#include "types.h"

class DirectionalLight : public Light {

public:
    R3 d; // light-to-scene direction
    void direction(
            const R3& p,
            R3& d,
            double& max_t
    ) const;
};

#endif //RAYMARCHER_DIRECTIONALLIGHT_H
