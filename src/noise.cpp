//
// Created by disconcision on 22/03/19.
//

#include "noise.h"
#include "geometry.h"
#include "Objects/types.h"
#include <iostream>



R3 randomR3(R3 seed) {
  /* generate a random direction in R3
   * REF: https://github.com/dilevin/computer-graphics-shader-pipeline */
  R2 s = R2(dot(seed, R3(127.1,311.7,783.089)),
            dot(seed, R3(269.5,183.3,173.542)));
  //todo: need to decl temp to disamgiguate?
  R2 temp = sin(s)*43758.5453123;
  R2 rv = fract(temp);
  Angle theta = acos(2*rv(0) - 1),
        phi = 2*M_PI*rv(1);
  return R3(cos(phi)*sin(theta),
            sin(phi)*sin(theta),
            cos(theta));
}


R noise(R3 seed) {
  /* an implementation of Perlin noise
   * REF: https://www.scratchapixel.com/lessons/procedural-generation-virtual-worlds/perlin-noise-part-2 */

  /* tile space with unit cubes */
  R3 current_cell = floor(seed);
  R3 position_in_cell = fract(seed); // todo: ambiguity error when i try to overload fract for R3
  R3 smooth_in_cell = smooth_step(position_in_cell);

  /* pick random directions at the corners of the unit cube
     and dot with the direction from the seed to those corners */
  R c[2][2][2];
  for (N i=0; i<2; i++)
    for (N j=0; j<2; j++)
      for (N k=0; k<2; k++)
        c[i][j][k] = dot(randomR3(current_cell + R3(i,j,k)),
                         position_in_cell - R3(i,j,k));


  /* linearly interpolate between the values on the corners */
  R x = mix(mix(mix(c[0][0][0], c[1][0][0], smooth_in_cell(0)),
                mix(c[0][1][0], c[1][1][0], smooth_in_cell(0)),
                smooth_in_cell(1)),
            mix(mix(c[0][0][1], c[1][0][1], smooth_in_cell(0)),
                mix(c[0][1][1], c[1][1][1], smooth_in_cell(0)),
                smooth_in_cell(1)),
            smooth_in_cell(2));

  /* return a value in [0,1] */
  return 2*x - 1;
}


R turbulence(R3 s, R init_freq, R persistence) {
  /* superimpose exponentially scaled and attenuated perlin noise */
  R nonsense = 0, freq = init_freq, amp = 1, total = 0;
  const unsigned TURBULENCE_ITERATIONS = 8;
  for (int i=0; i<TURBULENCE_ITERATIONS; i++) {
    nonsense += cos(noise(freq*s))*amp;
    total += amp;
    amp *= persistence;
    freq *= 2;
  }
  return nonsense /= total;
}


R marble(R3 s, R3 period, R turb_factor, R init_freq, R persistence) {
  /* compose turbulent perlin noise with a regular periodic function */
  R base = dot(cMult(s, period), R3(1, 1, 1))
           + turb_factor*turbulence(s, init_freq, persistence);
  return abs(sin(base*M_PI));
}
