//
// Created by disconcision on 19/03/19.
//

#ifndef RAYMARCHER_RIGID_H
#define RAYMARCHER_RIGID_H

#include "Objects/types.h"

/* translates sdf f through displacement d */
auto move (R3 d, SDF f) -> SDF;

/* affine-transforms SDF f according to the
 * INVERSE of the provided transformation */
auto affine (R4x4 T_inv, SDF f) -> SDF;

/* rotate SDF f through angle a (radians) */
auto rotate_x (R a, SDF f) -> SDF;
auto rotate_y (R a, SDF f) -> SDF;;
auto rotate_z (R a, SDF f) -> SDF;;


#endif //RAYMARCHER_RIGID_H
