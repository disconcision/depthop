//
// Created by disconcision on 21/03/19.
//

#ifndef RAYMARCHER_PRIMITIVES_H
#define RAYMARCHER_PRIMITIVES_H

#include "Objects/types.h"


/* unit sphere at origin */
auto sphere (R3 x) -> R;

/* unit cube at origin */
auto box (R3 x) -> R;

/* upward-facing flat y-axis plane at origin */
auto plane (R3 x) -> R;

/* infinite unit y-axis cylinder at origin */
auto cylinder (R3 x) -> R;


#endif //RAYMARCHER_PRIMITIVES_H
