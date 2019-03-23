//
// Created by disconcision on 21/03/19.
//

#ifndef RAYMARCHER_CONSTANTS_H
#define RAYMARCHER_CONSTANTS_H


/* OpenMP parallelization */
#define NUM_THREADS 6


/* IMAGES */
const unsigned DEFAULT_WIDTH = 400;
const unsigned DEFAULT_HEIGHT = 400;
const std::string FILENAME = "scene.ppm";


/* MARCHING */
const R MIN_D = 0.0;
const R MAX_D = 200.0;

const unsigned MARCH_MAX_STEPS = 180;
const R EPSILON_MARCH = 1e-5;


/* SHADING */
const bool COLOR_STEPS = false;
const bool COLOR_NORMAL = false;
const R EPSILON_NORMAL = 1e-3;


/* SHADOWS */
const bool SHADOWS_ENABLED = true;
const unsigned MAX_STEPS_SHADOW = 160;
const R EPSILON_SHADOW = 1e-5;
const R SOFTNESS = 4.0; // 1: very soft to 64: very hard


/* AMBIENT OCCLUSION */
const bool AO_ENABLED = true;
const bool AO_STEP_ENABLED = false;
const R MIN_D_SHADOW = 1e-1;
const unsigned MAX_STEPS_AO = 5;
const R STEP_SIZE_AO = 0.3;


#endif //RAYMARCHER_CONSTANTS_H
