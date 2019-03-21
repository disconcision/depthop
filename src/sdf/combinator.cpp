//
// Created by disconcision on 21/03/19.
//

#include "sdf/combinator.h"
#include "geometry.h"

/* union of two distance fields */
auto join (SDF f, SDF g) -> SDF {
  return [f, g] (R3 x) {
      return min(f(x), g(x));};}


/* intersection of two distance fields */
auto intersect (SDF f, SDF g) -> SDF {
  return [f, g] (R3 x) {
      return max(f(x), g(x));};}


/* subtract the second sdf from the first */
auto subtract (SDF f, SDF g) -> SDF {
  return [f, g] (R3 x) {
      return max(f(x), -g(x));};}


/* linearly interpolates between two sdfs.
 * a=0 means all f, a=1 means all g */
auto blend (R a, SDF f, SDF g) -> SDF {
  return [f, g, a] (R3 x) {
      return a*f(x) + (1 - a)*g(x);};}


/* smoothly unions two sdfs with smoothness s
 * s=0 todo */
auto smooth_join (R s, SDF f, SDF g) -> SDF {
  return [f, g, s] (R3 x) {
      return -log2(exp2(-s*f(x)) + exp2(-s*g(x)))/s;};}


/* todo */
auto smooth_join_p (SDF f, SDF g, R k) -> SDF {
  return [f, g, k] (R3 x) {
      R a = f(x), b = g(x);
      R h = clamp(0.5 + 0.5*(b - a)/k, 0, 1);
      return mix(b,a,h) - k*h*(1 - h);};}


/* todo */
auto smooth_sub_p (SDF f, SDF g, R k) -> SDF {
  return [f, g, k] (R3 x) {
      R a = f(x), b = g(x);
      R h = clamp(0.5 - 0.5*(b + a)/k, 0, 1);
      return mix(b,-a,h) + k*h*(1 - h);};}