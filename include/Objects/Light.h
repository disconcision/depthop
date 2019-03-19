//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_LIGHT_H
#define RAYMARCHER_LIGHT_H

#include "types.h"

class Light {

public:
    Color I;
    virtual ~Light() {};
    virtual void direction(
            const vec3& p, // query point
            vec3& d, //  p-to-light direction
            double& max_t // p-to-light distance
            ) const =0;
};

#endif //RAYMARCHER_LIGHT_H
