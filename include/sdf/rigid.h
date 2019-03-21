//
// Created by disconcision on 19/03/19.
//

#ifndef RAYMARCHER_RIGID_H
#define RAYMARCHER_RIGID_H

#include "Objects/types.h"


template <typename SDF_>
auto affine (R4x4 T_inv, SDF_ f);

template <typename SDF_>
auto rotate_x (R a, SDF_ f);

// std::function<SDF(R,SDF)>
template <typename SDF_>
auto rotate_y (R a, SDF_ f);

template <typename SDF_>
auto rotate_z (R a, SDF_ f);


#endif //RAYMARCHER_RIGID_H
