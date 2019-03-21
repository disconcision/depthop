//
// Created by disconcision on 16/03/19.
//

#include "shade.h"
#include "geometry.h"
//#include <iostream>


double march_softshadow(
        const Ray& ray,
        double (&sdf)(R3),
        const double min_d,
        const double max_d) {
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
  double depth = min_d;
  unsigned MAX_STEPS = 160;
  double EPSILON = 1e-5;
  double shadow_factor = 1.0; // initial value; falling
  double softness = 4; // 1: very soft to 64: very hard

  for (unsigned i=0; i < MAX_STEPS; i++) {
    double d = sdf(ray.origin + depth*ray.direction);
    if (d < EPSILON) return 0.0;
    shadow_factor = min(shadow_factor, softness*d/depth);
    depth += d;
    if (depth >= max_d) break;
  }
  return shadow_factor;
}


double ambient_occlusion(
        double (&sdf)(R3),
        const R3 &p,
        const R3 &n) {
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
  double depth = 1e-2;
  unsigned MAX_STEPS = 5;
  double step_size = 0.3;
  double occlusion_factor = 1.0;
  Ray ray = Ray(p,n);

  for (unsigned i=1; i < MAX_STEPS; i++) {
    double distance = sdf(follow(ray, depth));
    depth += step_size;
    occlusion_factor -= (depth - distance)/(i*i);//(pow(2,i));
  }
  return occlusion_factor;
}




R3 cMult(R3 a, R3 b) {
  return (a.array() * b.array()).matrix();
}


Color shade_blinn_phong(
        const Ray &ray,
        double (&sdf)(R3),
        const int &hit_id,
        const double &depth,
        const R3 &n,
        const Lights &lights) {

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

  for (auto &light : lights) {

    R3 point = follow(ray, depth);

    // determine light direction & distance
    R3 light_direction;
    double max_d;
    light->direction(point, light_direction, max_d);
    Color I = light->I;

    // determine shadow factor
    Ray shadow_ray(point, light_direction);
    double light_occlusion = 1.0;
    double EPSILON = 1e-1;
    if(light->castShadows)
      /* EPSILON offset to avoid self-shadowing */
      light_occlusion = march_softshadow(shadow_ray, sdf, EPSILON, max_d);

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


//lightray(ray, hit_id, n, depth);
Color shade(
        const Ray& ray,
        double (&sdf)(R3),
        const Lights& lights,
        const int hit_id,
        const R3& n,
        const double depth) {

  return shade_blinn_phong(ray, sdf, hit_id, depth, n, lights);
}



