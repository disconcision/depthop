//
// Created by disconcision on 19/03/19.
//

#include "field.h"
#include <Eigen/Geometry>


// https://stackoverflow.com/questions/6458612/c0x-proper-way-to-receive-a-lambda-as-parameter-by-reference
// or at top level:
// template<typename F>
// void f(F &lambda) { /* ... */}

/*
template<typename SDF2>
auto join2(SDF2 &f, SDF2 &g) {
    return [&f, &g] (R3& x) {
        return min(f(x), g(x));};}

template<typename SDF2>
auto scale2(R s, SDF2 &f) {
    return [&f, s] (R3& x) {
        return s*f(x/s);};};
*/

// ref: https://www.alanzucconi.com/2016/07/01/signed-distance-functions/


double field(vec3 p) {

  SDF sphere = [] (const R3 x) {
      return x.norm() - 1.0;};

  SDF box = [] (const R3 x) {
      return (x.cwiseAbs() - R3(0.17,0.5,3.0)).maxCoeff();};

  R4x4 transl, transl_inv, transl_inv_bake;
  transl << 1.0, 0.0, 0.0, 0.5,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;
  transl_inv_bake << 1.0, 0.0, 0.0, -0.5,
                     0.0, 1.0, 0.0, 0.0,
                     0.0, 0.0, 1.0, 0.0,
                     0.0, 0.0, 0.0, 1.0;
  //transl_inv = transl.inverse();
  // todo: precalc this?

  /* move :: (R3, SDF) -> SDF
   * translates SDF through displacement d */
  auto move = [] (R3 d, SDF f) {
      return [f, d] (R3 x) {
          return f(x - d);};};

  /* affine :: (R4x4, SDF) -> SDF
   * affine-transforms the SDF according to the
   * INVERSE of the provided transformation */
  auto affine = [] (R4x4 T_inv, SDF f) {
      return [f, T_inv] (R3 x) {
          R4 t = T_inv*R4(x(0),x(1),x(2),1);
          return f(R3(t(0),t(1),t(2)));};};


  /* complement :: SDF -> SDF
   * makes the inside, out */
  auto complement = [] (SDF f) {
      return [f] (R3 x) {
          return -f(x);};};

  /* scale :: (R, SDF) -> SDF
   * uniformly scales an sdf by a factor of a */
  auto scale = [] (R s, SDF f) {
      return [f, s] (R3 x) {
          return s*f(x/s);};};

  /* join :: (SDF, SDF) -> SDF
   * union of two distance fields */
  auto join = [] (SDF f, SDF g) {
      return [f, g] (R3 x) {
          return min(f(x), g(x));};};

  /* intersect :: (SDF, SDF) -> SDF
   * intersection of two distance fields */
  auto intersect = [] (SDF f, SDF g) {
      return [f, g] (R3 x) {
          return max(f(x), g(x));};};

  /* subtract :: (SDF, SDF) -> SDF
   * subtract the second sdf from the first */
  auto subtract = [] (SDF f, SDF g) {
      return [f, g] (R3 x) {
          return max(f(x), -g(x));};};

  /* blend :: (SDF, SDF, R) -> SDF
   * linearly interpolates between two sdfs.
   * a=0 means all f, a=1 means all g */
  auto blend = [] (SDF f, SDF g, R a) {
      return [f, g, a] (R3 x) {
          return a*f(x) + (1 - a)*g(x);};};

  /* smooth_join :: (SDF, SDF, R) -> SDF
   * smoothly unions two sdfs. s is a smoothness parameter. */
  auto smooth_join = [] (SDF f, SDF g, R s) -> SDF {
      return [f, g, s] (R3 x) {
          return -log2(exp2(-s*f(x)) + exp2(-s*g(x)))/s;};};

  // join is of type std::function<SDF(SDF, SDF)>

  // expanded version takes about half the time:
  //return -log2(exp2(-20*0.9*sphere((p-vec3(-0.5,0,0))/0.9)) + exp2(-20*(sphere(p-vec3(0.5,0,0)))))/20;

  //return sphere(p);
  //return scale(1.5, sphere)(p);
  //return move(R3(-0.5,0,0), sphere)(p);
  //return affine(transl, sphere)(p);
  //return (blend(box, sphere, 0.2))(p);
  return smooth_join(move(R3(-0.5,0,0), scale(0.9, sphere)),
                     move(R3(0.5,0,0), sphere), 20)(p);
}


