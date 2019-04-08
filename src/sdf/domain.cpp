//
// Created by disconcision on 21/03/19.
//

#include "sdf/domain.h"
#include "geometry.h"


/* make the inside, out */
auto complement (SDF f) -> SDF {
  return [f] (R3 x) {
    return -f(x);};}


/* ascend or descent level sets by r
 * ref: https://www.alanzucconi.com/2016/07/01/signed-distance-functions */
auto round (R r, SDF f) -> SDF {
  return [f, r] (R3 x) {
    return f(x) - r;};}


/* uniformly scales sdf f by a factor of s */
auto scale (R s, SDF f) -> SDF {
  return [f, s] (R3 x) {
    return s*f(x/s);};}


/* tile space with contents of f inside
 * the dxdxd cube centered at the origin */
auto repeat (R3 d, SDF f) -> SDF {
  return [d, f] (R3 x) {
    return f(mod(x,d) - 0.5*d);};}


/* tile space with contents of f inside d units
 * along the x-axis centered at the origin */
auto repeat_x (R d, SDF f) -> SDF {
  return [d, f] (R3 x) {
    return f(R3(mod(x(0), d) - 0.5*d, x(1), x(2)));};}


/* repeat f in a circle a times
 * ref: https://blog.thrill-project.com/zwerg-distance-field-editor */
auto circular_y (R a, SDF f) -> SDF {
  return [f, a] (R3 x) {
    R3 v = R3(atan(x(2)/x(0))*a/(2*M_PI), x(1), R2(x(0), x(2)).norm());
    return f(v);};}