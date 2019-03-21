//
// Created by disconcision on 21/03/19.
//

#ifndef RAYMARCHER_DOMAIN_H
#define RAYMARCHER_DOMAIN_H

#include "Objects/types.h"


/* make the inside, out */
auto complement (SDF f) -> SDF;

/* ascend or descent level sets by r */
auto round (R r, SDF f) -> SDF;

/* uniformly scales sdf f by a factor of a */
auto scale (R s, SDF f) -> SDF;

/* tile space with contents of f inside
 * the dxdxd cube centered at the origin */
auto repeat (R3 d, SDF f) -> SDF;

/* tile space with contents of f inside d units
 * along the x-axis centered at the origin */
auto repeat_x (R d, SDF f) -> SDF;

/* todo: wtf do i do */
auto circular_y (R a, SDF f) -> SDF;


#endif //RAYMARCHER_DOMAIN_H
