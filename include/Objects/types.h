//
// Created by disconcision on 16/03/19.
//

#ifndef RAYMARCHER_TYPES_H
#define RAYMARCHER_TYPES_H

#include <Eigen/Core>
#include <limits>
#include <vector>
#include <functional>


using std::max;
using std::min;

const double DBL_INFINITY = std::numeric_limits<double>::infinity();

using Color = Eigen::Vector3d;

using R = double;
using R2 = Eigen::Vector2d;
using R3 = Eigen::Vector3d;
using R4 = Eigen::Vector4d;
using R2x2 = Eigen::Matrix2d;
using R3x3 = Eigen::Matrix3d;
using R4x4 = Eigen::Matrix4d;

using SDF = std::function<R(R3)>;


#endif //RAYMARCHER_TYPES_H
