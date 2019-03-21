//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_RAY_H
#define RAYMARCHER_RAY_H

#include "types.h"

struct Ray {

  R3 origin;
  R3 direction;

  Ray (R3 o, R3 d) {
    this->origin = o;
    this->direction = d;
  }

  /*
  R3 follow(R depth) {
    return this->origin + depth*this->direction;
  }
  */

};

#endif  //RAYMARCHER_RAY_H
