//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_TYPES_H
#define RAYMARCHER_TYPES_H

#include <Eigen/Core>
#include <limits>
#include <vector>
#include <algorithm>
#include <functional>

using vec2 = Eigen::Vector2d;
using vec3 = Eigen::Vector3d;
using mat3 = Eigen::Matrix3d;
using mat4 = Eigen::Matrix4d;
using Color = Eigen::Vector3d;

using std::max;
using std::min;

const double DBL_INFINITY = std::numeric_limits<double>::infinity();

using R = double;
using R3 = Eigen::Vector3d;
using R4 = Eigen::Vector4d;
using R4x4 = Eigen::Matrix4d;
using R3x4 = Eigen::MatrixXd;

using SDF = std::function<R(R3)>;



#endif //RAYMARCHER_TYPES_H
