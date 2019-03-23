//
// Created by disconcision on 22/03/19.
//

#ifndef RAYMARCHER_NOISE_H
#define RAYMARCHER_NOISE_H

#include "Objects/types.h"


/* perlin noise R3 -> R */
R noise(R3 seed);

/* superimpose exponentially scaled and attenuated perlin noise */
R turbulence(R3 s, R init_freq, R persistence);

/* compose turbulent perlin noise with a regular period */
R marble(R3 s, R3 period, R turb_factor, R init_freq, R persistence);


#endif //RAYMARCHER_NOISE_H
