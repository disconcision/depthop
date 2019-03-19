//
// Created by disconcision on 19/03/19.
//

#ifndef RAYMARCHER_FIELD_H
#define RAYMARCHER_FIELD_H

#include "Objects/types.h"

using R = double;
using R3 = Eigen::Vector3d;
using R4 = Eigen::Vector4d;
using R4x4 = Eigen::Matrix4d;
using R3x4 = Eigen::MatrixXd;

using SDF = std::function<R(R3)>;

double field(vec3 p);

#endif //RAYMARCHER_FIELD_H
