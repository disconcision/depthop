//
// Created by disconcision on 19/03/19.
//

#include "field.h"

#include "sdf/rigid.h"
#include "sdf/primitives.h"
#include "sdf/domain.h"
#include "sdf/combinator.h"


// https://stackoverflow.com/questions/6458612/c0x-proper-way-to-receive-a-lambda-as-parameter-by-reference
// or at top level:
// template<typename F>
// void f(F &lambda) { /* ... */}

// ref: https://www.alanzucconi.com/2016/07/01/signed-distance-functions/
// ref: https://blog.thrill-project.com/zwerg-distance-field-editor/
// for circular repetition technique


R field(R3 p) {

  // expanded version takes about half the time:
  //return -log2(exp2(-20*0.9*sphere((p-vec3(-0.5,0,0))/0.9)) + exp2(-20*(sphere(p-vec3(0.5,0,0)))))/20;

  //return sphere(p);
  //return scale(1.5, sphere)(p);
  //return move(R3(-0.5,0,0), sphere)(p);
  //return affine(transl, sphere)(p);
  //return (blend(0.2,box, sphere))(p);

  auto f = move(R3(-0.1,0.5,0),rotate_y(-0.3,round(0.1, box)));
  auto butt = smooth_join(30, move(R3(-0.5,0,0), scale(0.9, sphere)),
                          move(R3(0.5,0,0), sphere));
  auto g = rotate_z(0.4,smooth_sub_p(f, butt, 0.1));
  auto final = join(scale(0.8,g),repeat(R3(1,2,3),scale(0.2,g)));
  //return final(p);

  auto row = move(R3(0,0,2),repeat_x(1,scale(0.4, sphere)));
  auto ring = rotate_x(3.1415/2,circular_y(12,row));
  auto col_row =  move(R3(0,0,2),repeat_x(1,scale(0.1, cylinder)));
  auto col_ring = circular_y(12,col_row);
  //return col_ring(p);

  auto god = sphere;
  //return god(p);
  return smooth_join(12, scale(1,col_ring),
          join(god,move(R3(0,-1,0),plane)))(p);
  return join(ring,repeat(R3(8,8,8),ring))(p);
}


