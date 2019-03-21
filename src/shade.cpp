//
// Created by disconcision on 16/03/19.
//

#include "shade.h"
#include <iostream>
//#include <algorithm>



double march_softshadow(
        const Ray& ray,
        double (&sdf)(vec3),
        const double min_d,
        const double max_d) {

  double depth = min_d;
  unsigned MAX_STEPS = 160;
  double EPSILON = 1e-5;
  double shadow_factor = 1.0;
  double softness = 4; /* 1: very soft, 64: very hard*/

  /* SDF SOFT SHADOWS
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
        double (&sdf)(vec3),
        const vec3 &p,
        const vec3 &n) {

  double depth = 1e-2;
  unsigned MAX_STEPS = 5;
  double step_size = 0.3;
  double occ_factor = 1.0;
  Ray ray;
  ray.origin = p;
  ray.direction = n;

  /* SDF AMBIENT OCCLUSION
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


  for (unsigned i=1; i < MAX_STEPS; i++) {
    double d = sdf(ray.origin + depth*ray.direction);
    depth += step_size;
    occ_factor -= (depth - d)/(i*i);//(pow(2,i));
  }
  return occ_factor;
}




vec3 cMult(vec3 a, vec3 b) {
  return (a.array() * b.array()).matrix();
}


Color shade_blinn_phong(
        const Ray &ray,
        double (&sdf)(vec3),
        const int &hit_id,
        const double &t,
        const vec3 &n,
        Lights &lights) {

  Color rgb = Color(0,0,0);

  // ambient light intensity
  vec3 Ia = vec3(0.1,0.1,0.1);

  // offset to avoid self-shadowing
  double epsilon = 1e-5;

  for (auto &light : lights) {

    // point on object p = e + t*d
    vec3 p = ray.origin+t*ray.direction;

    // determine light direction & distance
    vec3 l;
    double max_d;
    light->direction(p,l,max_d);
    Color I = light->I;

    // determine shadow factor
    Ray shadow_ray;
    shadow_ray.origin = p;
    shadow_ray.direction = l;
    double light_occlusion;
    if(light->castShadows)
      light_occlusion = march_softshadow(shadow_ray, sdf,1e-1,max_d);
    else
      light_occlusion = 1.0;
    //std::cout << light_occlusion << "\n";

    // todo: get material properties
    //auto materal = some_function[hit_id]->material;
    double alpha = 2000;
    Color ka = Color(0.1,0.1,0.1),
          kd = Color(0.7,0.7,0.7),
          ks = Color(0.8,0.8,0.8);

    // add ambient light contribution
    rgb += cMult(Ia, ka);

    int new_hit_id;

    // find half-angle vector for specular reflections
    vec3 v = -ray.direction.normalized();
    vec3 h = (l + v).normalized();

    // add diffuse and specular contribution for this light
    rgb += light_occlusion* (cMult(I, kd * (std::max(0.0, n.dot(l))))
            + cMult(I, ks * pow(std::max(0.0, n.dot(h)), alpha)));

  }

  //return Color(1,1,1)*ambient_occlusion(sdf,ray.origin+t*ray.direction,n);
  double ao = ambient_occlusion(sdf,ray.origin+t*ray.direction,n);
  return rgb*ao;
}


//lightray(ray, hit_id, n, depth);
Color shade(
        const Ray &ray,
        double (&sdf)(vec3),
        const int hit_id,
        const vec3 &n,
        const double depth) {

  Lights lights;
  std::shared_ptr<DirectionalLight> light0(new DirectionalLight());
  light0->d = vec3(-1,-1,-1);
  light0->I = vec3(0.8,0.8,0.8);
  light0->castShadows = true;
  lights.push_back(light0);
  std::shared_ptr<DirectionalLight> light1(new DirectionalLight());
  light1->d = vec3(-0,1,0);
  light1->I = vec3(0,0.3,0.8);
  light1->castShadows = false;
  lights.push_back(light1);
  return shade_blinn_phong(ray, sdf, hit_id, depth, n, lights);
}



