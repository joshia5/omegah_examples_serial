#include <Omega_h_file.hpp>
#include <Omega_h_library.hpp>
#include <Omega_h_mesh.hpp>
#include "Omega_h_map.hpp"
#include "Omega_h_for.hpp"
#include "Omega_h_array_ops.hpp"
using namespace Omega_h;

int main(int argc, char** argv) {
  auto lib = Library(&argc, &argv);
  if(argc!=2) {
    fprintf(stderr, "Usage: %s <input mesh>\n", argv[0]);
    return 0;
  }
  const auto inmesh = argv[1];
  Mesh mesh(&lib);
  binary::read(inmesh, lib.world(), &mesh);

  //for single quad
/*
  LOs hl2l({0, 1, 1, 2, 2, 3, 0, 3}, "hl2l");
  auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  //auto l2hl = invert_map_by_atomics(hl2l, 4);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/

  //face to edge for single wedge
/*
  LOs hl2l({0, 1, 2, 0, 3, 5, 6, 1, 3, 4, 7, 2, 4, 5, 8, 6, 7, 8}, "hl2l");
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 9);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/
/*
  //face to edge for wedge on top of tet
  LOs hl2l({0, 1, 2, 0, 1, 4, 1, 2, 5, 3, 4, 5, 3,6,7,9,5,7,8,11,4,6,8,10,9, 10, 11}, "hl2l");
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 12);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/
/* This works and gives o/p {0,1,1,2,0,2,0,3,1,3,2,3,4,4,4}
  //tris to edge for wedge on top of tet
  LOs hl2l({0, 2, 3, 0, 1, 4, 1, 2, 5, 3, 4, 5, 9, 10, 11}, "hl2l");
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 12);
  //auto l2hl = invert_map_by_atomics(hl2l, 9); //note that we changed input from 9(nedges) to 12(max edge index+1)
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]/3);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/
  //quads to edge for wedge on top of tet
  // Works with output {0,2,1,0,2,0,1,1,2,0,2,1} // note here that the output is sorted with increasing index of edges as per the down asjacencies, i.e. edge 3 is adjacent to quad 0, 4to2, .., 6 to 0&2 and so on
  LOs hl2l({3, 6, 7, 9, 5, 7, 8, 11, 4, 6, 8, 10}, "hl2l");
  auto l2hl = invert_map_by_atomics(hl2l, 12);  //note that we changed input to 12(max edge index+1)
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]/4);
  };
  parallel_for(l2hl.ab2b.size(),f);

/*
  //cell to face for wedge on top of tet
  LOs hl2l({0, 1, 2, 3, 3, 4, 5, 6, 7}, "hl2l");
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 8);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/
/*This works
  //wedge to face for wedge on top of tet
  //LOs hl2l({3, 4, 0, 1, 2}, "hl2l");//we used different indices for tri and quad
  LOs hl2l({0, 1, 0, 1, 2}, "hl2l");// this is for the formal document's example
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 3);
  //auto l2hl = invert_map_by_atomics(hl2l, 5);//note we changed nb value from(nfaces) to (max face in hl2l+1)
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]/5);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/
  return 0;
}
