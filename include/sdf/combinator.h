//
// Created by disconcision on 21/03/19.
//

#ifndef RAYMARCHER_COMBINATOR_H
#define RAYMARCHER_COMBINATOR_H

#include "Objects/types.h"

/* union of two distance fields */
auto join (SDF f, SDF g) -> SDF;

/* intersection of two distance fields */
auto intersect (SDF f, SDF g) -> SDF;

/* subtract the second sdf from the first */
auto subtract (SDF f, SDF g) -> SDF;

/* linearly interpolates between two sdfs.
 * a=0 means all f, a=1 means all g */
auto blend (R a, SDF f, SDF g) -> SDF;

/* smoothly unions two sdfs with smoothness s
 * s=0 todo */
auto smooth_join (R s, SDF f, SDF g) -> SDF;

/* todo */
auto smooth_join_p (SDF f, SDF g, R k) -> SDF;

/* todo */
auto smooth_sub_p (SDF f, SDF g, R k) -> SDF;


#endif //RAYMARCHER_COMBINATOR_H
