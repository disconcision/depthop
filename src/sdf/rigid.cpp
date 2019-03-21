//
// Created by disconcision on 19/03/19.
//

#include "sdf/rigid.h"


/* affine :: (R4x4, SDF) -> SDF
* affine-transforms the SDF according to the
* INVERSE of the provided transformation */
template <typename SDF_>
auto affine (R4x4 T_inv, SDF_ f) {
    return [f, T_inv] (R3 x) {
        R4 t = T_inv*R4(x(0),x(1),x(2),1);
        return f(R3(t(0),t(1),t(2)));};};

template <typename SDF_>
auto rotate_x (R a, SDF_ f) {
    R4x4 T;
    T << 1,       0,        0, 0,
            0, cos(-a), -sin(-a), 0,
            0, sin(-a),  cos(-a), 0,
            0,       0,        0, 1;
    return affine(T, f);};

template <typename SDF_>
auto rotate_y (R a, SDF f) {
    R4x4 T;
    T <<  cos(-a), 0, sin(-a), 0,
            0,       1,       0, 0,
            -sin(-a), 0, cos(-a), 0,
            0,       0,       0, 1;
    return affine(T, f);};

template <typename SDF_>
auto rotate_z (R a, SDF f) {
    R4x4 T;
    T << cos(-a), -sin(-a), 0, 0,
            sin(-a),  cos(-a), 0, 0,
            0,        0,       1, 0,
            0,        0,       0, 1;
    return affine(T, f);};
