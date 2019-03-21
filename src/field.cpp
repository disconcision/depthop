//
// Created by disconcision on 19/03/19.
//

#include "field.h"
#include <Eigen/Geometry>
#include <algorithm>

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



double mod1(double x, double y) {
  return x - y*floor(x/y);
}

R3 mod(R3 x, R3 y) {
  return R3(mod1(x(0),y(0)),mod1(x(1),y(1)),mod1(x(2),y(2)));
}

double clamp(double x, double lo, double hi) {
  return min(hi, max(x, lo));
}

double mix(double x, double y, double a) {
  return (1 - a)*x + a*y;
}


// ref: https://blog.thrill-project.com/zwerg-distance-field-editor/
// for circular repetition technique

auto sphere (const R3 x) -> R {
  return x.norm() - 1.0;};

auto box (const R3 x) -> R {
  return (x.cwiseAbs() - R3(1,1,1)).maxCoeff();};

auto plane (const R3 x) -> R {
  return x.dot(R3(0,1,0));};

auto cylinder (const R3 x) -> R {
    return vec2(x(0),x(2)).norm() - 1;};



/* move :: (R3, SDF) -> SDF
 * translates SDF through displacement d */
auto move (R3 d, SDF f) -> SDF {
  return [f, d] (R3 x) {
    return f(x - d);};}


/* complement :: SDF -> SDF
 * makes the inside, out */
auto complement = [] (SDF f) {
    return [f] (R3 x) {
        return -f(x);};};


/* round :: (SDF, R) -> SDF
 * ascend or descent r units to a higher
 * or lower level set */
auto round (R r, SDF f) -> SDF {
  return [f, r] (R3 x) {
      return f(x) - r;};};


/* scale :: (R, SDF) -> SDF
 * uniformly scales an sdf by a factor of a */
auto scale (R s, SDF f) {
    return [f, s] (R3 x) {
        return s*f(x/s);};};


/* join :: (SDF, SDF) -> SDF i.e. std::function<SDF(SDF, SDF)>
 * union of two distance fields */
auto join (SDF f, SDF g) -> SDF {
  return [f, g] (R3 x) {
      return min(f(x), g(x));};}


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


auto repeat (R3 d, SDF f) -> SDF {
  return [d, f] (R3 x) {
      return f(mod(x,d) - 0.5*d);};};


auto repeat_x (R d, SDF f) -> SDF {
  return [d, f] (R3 x) {
      return f(R3(mod1(x(0),d) - 0.5*d,x(1),x(2)));};};



/* smooth_join :: (SDF, SDF, R) -> SDF
 * smoothly unions two sdfs. s is a smoothness parameter. */
auto smooth_join (SDF f, SDF g, R s) -> SDF {
    return [f, g, s] (R3 x) {
        return -log2(exp2(-s*f(x)) + exp2(-s*g(x)))/s;};};

auto smooth_join_p = [] (SDF f, SDF g, R k) -> SDF {
    return [f, g, k] (R3 x) {
        R a = f(x), b = g(x);
        R h = clamp(0.5 + 0.5*(b - a)/k, 0, 1);
        return mix(b,a,h) - k*h*(1 - h);};};

auto smooth_sub_p = [] (SDF f, SDF g, R k) -> SDF {
    return [f, g, k] (R3 x) {
        R a = f(x), b = g(x);
        R h = clamp(0.5 - 0.5*(b + a)/k, 0, 1);
        return mix(b,-a,h) + k*h*(1 - h);};};







auto circular_y = [] (R a, SDF f) -> SDF {
    return [f, a] (R3 x) {
        R3 v = R3(atan(x(2)/x(0))*a/(2*3.14159),x(1),vec2(x(0), x(2)).norm());
        return f(v);};};



/* affine :: (R4x4, SDF) -> SDF
* affine-transforms the SDF according to the
* INVERSE of the provided transformation */
auto affine = [] (R4x4 T_inv, SDF f) {
    return [f, T_inv] (R3 x) {
        R4 t = T_inv*R4(x(0),x(1),x(2),1);
        return f(R3(t(0),t(1),t(2)));};};

auto rotate_x = [] (R a, SDF f) {
    R4x4 T;
    T << 1,       0,        0, 0,
            0, cos(-a), -sin(-a), 0,
            0, sin(-a),  cos(-a), 0,
            0,       0,        0, 1;
    return affine(T, f);};

auto rotate_y = [] (R a, SDF f) {
    R4x4 T;
    T <<  cos(-a), 0, sin(-a), 0,
            0,       1,       0, 0,
            -sin(-a), 0, cos(-a), 0,
            0,       0,       0, 1;
    return affine(T, f);};

auto rotate_z = [] (R a, SDF f) {
    R4x4 T;
    T << cos(-a), -sin(-a), 0, 0,
            sin(-a),  cos(-a), 0, 0,
            0,        0,       1, 0,
            0,        0,       0, 1;
    return affine(T, f);};



double field(vec3 p) {



  R4x4 transl;
  transl << 1.0, 0.0, 0.0, 0.5,
            0.0, 1.0, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0;





  // expanded version takes about half the time:
  //return -log2(exp2(-20*0.9*sphere((p-vec3(-0.5,0,0))/0.9)) + exp2(-20*(sphere(p-vec3(0.5,0,0)))))/20;

  //return sphere(p);
  //return scale(1.5, sphere)(p);
  //return move(R3(-0.5,0,0), sphere)(p);
  //return affine(transl, sphere)(p);
  //return (blend(box, sphere, 0.2))(p);
  auto f = move(R3(-0.1,0.5,0),rotate_y(-0.3,round(0.1, box)));
  auto butt = smooth_join(move(R3(-0.5,0,0), scale(0.9, sphere)),
                          move(R3(0.5,0,0), sphere), 30);
  auto g = rotate_z(0.4,smooth_sub_p(f, butt, 0.1));
  auto final = join(scale(0.8,g),repeat(R3(1,2,3),scale(0.2,g)));

  auto row = move(R3(0,0,2),repeat_x(1,scale(0.4, sphere)));

  auto ring = rotate_x(3.1415/2,circular_y(12,row));
  //return cylinder(p);
  //return final(p);
  auto col_row =  move(R3(0,0,2),repeat_x(1,scale(0.1, cylinder)));
  auto col_ring = circular_y(12,col_row);
  //return col_ring(p);
  auto god = sphere;
  //return god(p);
  return smooth_join(scale(1,col_ring),
          join(god,move(R3(0,-1,0),plane)),12)(p);
  return join(ring,repeat(R3(8,8,8),ring))(p);
}


