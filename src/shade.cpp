//
// Created by disconcision on 16/03/19.
//

#include "shade.h"
#include "geometry.h"
//#include <iostream>


double soft_shadow(
        const Ray &ray,
        R (&sdf)(R3),
        const R min_d,
        const R max_d) {
  /*
   * SDF SOFT SHADOWS
   *
   * As in raytracing, we follow a ray from the object
   * towards the light. Instead of just looking for
   * intersections, though, we track the point of closest
   * approach to the field (approximated as the minimum d
   * value during marching), normalized by the distance to
   * the object at that approach. An additional softness
   * parameter is used to modulate this effect.
   *
   * REF: https://iquilezles.org/www/articles/rmshadows/rmshadows.htm
   *
   */
  const unsigned MAX_STEPS = 160;
  const R EPSILON = 1e-5;
  const R softness = 4.0; // 1: very soft to 64: very hard
  R shadow_factor = 1.0; // initial value; falling
  R depth = min_d;

  for (unsigned i=0; i < MAX_STEPS; i++) {
    R distance = sdf(follow(ray, depth));
    if (distance < EPSILON) return 0.0;
    shadow_factor = min(shadow_factor, softness*distance/depth);
    depth += distance;
    if (depth >= max_d) break;
  }
  return clamp(shadow_factor, 0.0, 1.0);
}


double ambient_occlusion(
        R (&sdf)(R3),
        const R3& p,
        const R3& n) {
  /*
   * SDF AMBIENT OCCLUSION
   *
   * we follow the normal for a fixed number of fixed-size
   * steps. at each point, we compare the distance we've travelled
   * away from the object with the distance from our current
   * position along the normal to the closet point on our sdf.
   *
   * if this is zero, it means that there are no nearby point on
   * the geometry, so this sample contributes nothing to the occlusion.
   * otherwise, we normalize the difference by the current distance
   * to the surface, and add it to the overall occlusion factor.
   *
   * REF: http://9bitscience.blogspot.com/2013/07/
   *
   * */
  const unsigned MAX_STEPS = 5;
  const R step_size = 0.3;
  R occlusion_factor = 1.0;
  R depth = 1e-2;

  for (unsigned i=1; i < MAX_STEPS; i++) {
    R distance = sdf(follow(Ray(p,n), depth));
    depth += step_size;
    occlusion_factor -= (depth - distance)/(i*i);//(pow(2,i));
  }
  return occlusion_factor;
}




R3 cMult(R3 a, R3 b) {
  return (a.array() * b.array()).matrix();
}


Color shade_blinn_phong(
        const Ray& ray,
        R (&sdf)(R3),
        const unsigned& hit_id,
        const R& depth,
        const R3& n,
        const Lights& lights) {

  // todo: get material properties
  //auto material = some_function[hit_id]->material;
  double alpha = 800;
  Color ka = Color(0.1,0.1,0.1),
        kd = Color(0.7,0.7,0.7),
        ks = Color(0.8,0.8,0.8);

  Color rgb = Color(0,0,0);

  // add ambient light contribution
  R3 Ia = R3(0.1,0.1,0.1);
  rgb += cMult(Ia, ka);

  // ambient occlusion
  double ao = ambient_occlusion(sdf, follow(ray, depth), n);

  for (auto &light : lights.data) {

    R3 point = follow(ray, depth);

    // determine light direction & distance
    R3 light_direction;
    R max_d;
    light->direction(point, light_direction, max_d);
    Color I = light->I;

    // determine shadow factor
    Ray shadow_ray(point, light_direction);
    double light_occlusion = 1.0;
    const double EPSILON = 1e-1;
    if(light->castShadows)
      /* EPSILON offset to avoid self-shadowing */
      light_occlusion = soft_shadow(shadow_ray, sdf, EPSILON, max_d);

    // find half-angle vector for specular reflections
    // OLD: R3 v = normalize(-ray.direction);
    R3 h = normalize(light_direction - ray.direction);

    Color diffuse_factor = kd * max(0.0, dotR3(n, light_direction));
    Color specular_factor = ks * pow(max(0.0, dotR3(n, h)), alpha);

    rgb += light_occlusion * cMult(I, diffuse_factor + specular_factor);
  }

  // uncomment to eliminate cool noise on bkg
  return rgb*ao; //clampR3(rgb*ao,0,1);
}



Color shade(
        const Ray& ray,
        R (&sdf)(R3),
        const Lights& lights,
        const unsigned hit_id,
        const R3& n,
        const R depth) {

  return shade_blinn_phong(ray, sdf, hit_id, depth, n, lights);
}



