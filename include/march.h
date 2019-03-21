//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_MARCH_H
#define RAYMARCHER_MARCH_H

#include "Objects/Ray.h"
#include "Objects/types.h"


/* march along a ray towards towards the sdf
 * starting at depth min_d and returning the
 * depth to level set surface, up to max_d */
R march(
        const Ray& ray,
        R (&sdf)(R3),
        R min_d,
        R max_d,
        R3& n,
        unsigned& hit_id);


#endif //RAYMARCHER_MARCH_H