//
// Created by disconcision on 16/03/19.
//

#include "shade.h"
//#include <algorithm>

vec3 cMult(vec3 a, vec3 b) {
  return (a.array() * b.array()).matrix();
}


Color shade_blinn_phong(
        const Ray &ray,
        const int &hit_id,
        const double &t,
        const vec3 &n,
        Lights &lights) {

  Color rgb = Color(0,0,0);

  // ambient light intensity
  vec3 Ia = vec3(0.1,0.1,0.1);

  // offset to avoid self-shadowing
  double epsilon = 0.00001;

  for (auto &light : lights) {

    // point on object p = e + t*d
    vec3 p = ray.origin+t*ray.direction;

    // determine light direction & distance
    vec3 l;
    double max_t;
    light->direction(p,l,max_t);
    Color I = light->I;

    // get material properties
    //auto materal = some_function[hit_id]->material;
    double alpha = 2000;
    Color ka = Color(20.0/256,50.0/256,20.0/256),
          kd = Color(200.0/256,160.0/256,20.0/256),
          ks = Color(100.0/256,100.0/256,100.0/256);

    // add ambient light contribution
    rgb += cMult(Ia, ka);

    int new_hit_id;

    // find half-angle vector for specular reflections
    vec3 v = -ray.direction.normalized();
    vec3 h = (l + v).normalized();

    // add diffuse and specular contribution for this light
    rgb += cMult(I, kd * (std::max(0.0, n.dot(l))))
            + cMult(I, ks * pow(std::max(0.0, n.dot(h)), alpha));

  }

  return rgb;
}


//lightray(ray, hit_id, n, depth);
Color shade(
        const Ray &ray,
        const int hit_id,
        const vec3 &n,
        const double depth) {

  Lights lights;
  std::shared_ptr<DirectionalLight> light0(new DirectionalLight());
  light0->d = vec3(-1,-1,-1);
  light0->I = vec3(0.8,0.8,0.8);
  lights.push_back(light0);
  std::shared_ptr<DirectionalLight> light1(new DirectionalLight());
  light1->d = vec3(-0,1,0);
  light1->I = vec3(0,0.3,0.8);
  lights.push_back(light1);
  return shade_blinn_phong(ray, hit_id, depth, n, lights);
}



