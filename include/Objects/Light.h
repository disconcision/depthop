//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_LIGHT_H
#define RAYMARCHER_LIGHT_H

#include "types.h"
#include <memory>


class Light {

public:
    Color I;
    bool castShadows;
    virtual ~Light() {};
    virtual void direction(
            const R3& p, // query point
            R3& d, //  p-to-light direction
            double& max_t // p-to-light distance
            ) const =0;
};


using Lights =  std::vector<std::shared_ptr<Light>>;

#endif //RAYMARCHER_LIGHT_H
