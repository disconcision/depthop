//
// Created by disconcision on 16/03/19.
//

#include "shade.h"
#include "geometry.h"
#include "constants.h"
#include "noise.h"



#include <iostream>

R shadow_march(
        const Ray &ray,
        R (&sdf)(R3),
        const R max_d) {
  /*
   * SDF SOFT SHADOWS
   *
   * As in raytracing, we follow a ray from the object
   * towards the light. Instead of just looking for
   * intersections, though, we track the point of closest
   * approach to the field (stepwise approximated as the minimum d
   * value during marching), normalized by the distance to
   * the object at that approach. An additional softness
   * parameter is used to modulate this effect.
   *
   * REF: https://iquilezles.org/www/articles/rmshadows/rmshadows.htm
   *
   */
  R shadow_factor = 1.0; // initial value; falling
  R depth = MIN_D_SHADOW;

  for (unsigned i=0; i < MAX_STEPS_SHADOW; i++) {
    R distance = sdf(follow(ray, depth));
    if (distance < EPSILON_SHADOW) return 0.0;
    shadow_factor = min(shadow_factor, SOFTNESS*distance/depth);
    depth += distance;
    if (depth >= max_d) break;
  }
  return clamp(shadow_factor, 0.0, 1.0);
}

/*
R soft_shadows(
        R3 &point,
        Light &light,
        R (&sdf)(R3)) {


    // determine light direction & distance
    R3 light_direction;
    R max_d;
    light.direction(point, light_direction, max_d);
    Color I = light.I;

    // determine shadow factor
    Ray shadow_ray(point, light_direction);
    if(SHADOWS_ENABLED && light.castShadows)

        return shadow_march(shadow_ray, sdf, max_d);
    else return 1.0;
}
*/


R ambient_occlusion(
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
  R occlusion_factor = 1.0;
  R depth = 1e-2;

  for (unsigned i=1; i < MAX_STEPS_AO; i++) {
    R distance = sdf(follow(Ray(p,n), depth));
    depth += STEP_SIZE_AO;
    occlusion_factor -= (depth - distance)/(i*i);//(pow(2,i));
  }
  return occlusion_factor;
}




Color shade_blinn_phong(
        const Ray& ray,
        R (&sdf)(R3),
        const unsigned& hit_id,
        const R& depth,
        const R3& n,
        const Lights& lights) {

  // todo: implement materials
  double alpha = 800;
  Color ka = Color(0.1,0.1,0.1),
        kd = Color(0.7,0.7,0.7),
        ks = Color(0,0,0);

  Color rgb = Color(0,0,0);
  // add ambient light contribution
  R3 Ia = R3(0.1,0.1,0.1);
  rgb += cMult(Ia, ka);

  for (auto &light : lights.data) {

    R3 point = follow(ray, depth);

    R3 light_direction;
    R max_d;
    light->direction(point, light_direction, max_d);
    Color I = light->I;

    /* returns the occlusion factor at point
    * due to shadows in light cast by the sdf */
    R soft_shadows = 1.0;
    // determine shadow factor
    Ray shadow_ray(point, light_direction);
    if(SHADOWS_ENABLED && light->castShadows)
        soft_shadows = shadow_march(shadow_ray, sdf, max_d);

    // find half-angle vector for specular reflections
    R3 h = normalize(light_direction - ray.direction);

    Color diffuse = kd*max(0.0, dot(n, light_direction)),
          specular = ks * pow(max(0.0, dot(n, h)), alpha);

    rgb += soft_shadows * cMult(I, diffuse + specular);
  }

  // add noise (todo: refactor this)
  R3 point = follow(ray, depth);
  R nf = marble(point, R3(1.0, 0.5, 1.0), 4.8, 3.0, 0.55);
  R3 noise_factor = nf*Color(0.07,0.07,0.07);

  return noise_factor + rgb;
}



Color shade(
        const Ray& ray,
        R (&sdf)(R3),
        const Lights& lights,
        const R depth,
        unsigned& steps,
        const unsigned hit_id) {

  /* two alternate coloring schemes */
  if (COLOR_STEPS) {
    return Color(1,1,1)*steps/(double)MARCH_MAX_STEPS;
  } else if (COLOR_NORMAL) {
    return normal(sdf, follow(ray, depth))*0.5+0.5*Color(1,1,1);
  }

  R3 n = normal(sdf, follow(ray, depth));
  Color rgb;
  if (depth >= MAX_D) {
    rgb = Color(0.7,0.7,0.7);
  } else {
    rgb = shade_blinn_phong(ray, sdf, hit_id, depth, n, lights);

    if (AO_STEP_ENABLED) {
      rgb *= steps/(double)MARCH_MAX_STEPS;
    } else if (AO_ENABLED) {
      rgb += Color(0.5,0.5,0.5)*ambient_occlusion(sdf, follow(ray, depth), n);
    }
  }
  return clamp(rgb,0,1);//rgb;
}



