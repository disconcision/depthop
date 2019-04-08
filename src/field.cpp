//
// Created by disconcision on 19/03/19.
//

#include "field.h"

#include "sdf/rigid.h"
#include "sdf/primitive.h"
#include "sdf/domain.h"
#include "sdf/combinator.h"


R field(R3 p) {

  auto col_row =  move(R3(0,0,2),repeat_x(1,scale(0.1, cylinder)));
  auto col_ring = circular_y(12,col_row);

  auto base_pipe = scale(0.6, cylinder);
  auto pipes = join(
          rotate_z(90*(M_PI/180), base_pipe),
          join(base_pipe, rotate_x(90*(M_PI/180), base_pipe)));

  auto boi = rotate_y(20*(M_PI/180), subtract(sphere, pipes));
  auto boi_row =  move(R3(0,0,2),repeat_x(1,scale(0.35, boi)));
  auto boi_ring = move(R3(0,1.75,0), circular_y(12,boi_row));

  auto scene = join(boi_ring,
          join(move(R3(0,0.7,0),boi),
                  smooth_join(10, scale(0.6,col_ring),
                      move(R3(0,-1,0),plane))));

  return scene(p);
}

/* HERE LIES OZYMANDIAS
 * A MORE AMBITIOUS SCENE I DIDN'T HAVE TIME TO FINISH

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
    auto g = rotate_z(0.4,smooth_sub_p(0.1, f, butt));
    auto final = join(scale(0.8,g),repeat(R3(1,2,3),scale(0.2,g)));
    //return final(p);

    auto row = move(R3(0,0,2),repeat_x(1,scale(0.4, sphere)));
    auto ring = rotate_x(3.1415/2,circular_y(12,row));

    //return col_ring(p);

    auto torso = smooth_join(12,
                             ellipsoid(R3(1,1,1.2)),
                             move(R3(0,0.8,0),ellipsoid(R3(1.4,1,1.4))));

    auto limb = smooth_join(30,
                            move(R3(0,0.5,0),rotate_z(45/(2*M_PI), scale(1,ellipsoid(R3(2.1,1,2.1))))),
                            move(R3(0,-0.5,0),rotate_z(-45/(2*M_PI), ellipsoid(R3(2.1,1,2.1)))));

    auto legs = join(
            scale(1,move(R3(-1,-1,0.2), rotate_x(-80/(2*M_PI), rotate_y(180/(2*M_PI),limb)))),
            scale(1,move(R3(1,-1,0.2), rotate_x(-80/(2*M_PI), limb))));

    auto arms = scale(0.8,move(R3(0,1.5,0), legs));
    auto limbs = join(move(R3(0,0,0.4),arms),legs);
    auto body = smooth_join(20,
                            torso, limbs);
    auto head = sphere;

    //return join(boi, move(R3(0,-1,0),plane))(p);
    //return sphere(p);
    //auto rings = rotate_y(20*(M_PI/180),move(R3(4,40,400),repeat(R3(8,80,800),scale(0.6,col_ring))));
    //auto boi_field = move(R3(0,0,-20),rotate_y(0*(M_PI/180),move(R3(4,4,400),repeat(R3(8,8,800),boi))));
    //return boi_ring(p);
    //return join(ring,repeat(R3(8,8,8),ring))(p);

    auto god = scale(0.6,join(move(R3(0,2.6,0), head), body));
    auto gods = move(R3(4,40,4),repeat(R3(8,80,8),god));
}*/
