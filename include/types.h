//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_TYPES_H
#define RAYMARCHER_TYPES_H

#include <Eigen/Core>
#include <limits>
#include <vector>

using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using Color = Eigen::Vector3d;

const double DBL_INFINITY = std::numeric_limits<double>::infinity();

#endif //RAYMARCHER_TYPES_H
