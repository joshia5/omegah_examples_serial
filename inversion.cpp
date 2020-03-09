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
//for quad
/*
  LOs hl2l({0, 1, 1, 2, 2, 3, 0, 3}, "hl2l");
  auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  //auto l2hl = invert_map_by_atomics(hl2l, 4);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
*/

//for wedge
  LOs hl2l({0, 1, 2, 0, 3, 5, 6, 1, 3, 4, 7, 2, 4, 5, 8, 6, 7, 8}, "hl2l");
  //auto l2hl = invert_adj(Adj(hl2l), 2, 4, 1, 0);
  auto l2hl = invert_map_by_atomics(hl2l, 9);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, l2hl.ab2b[i]);
  };
  parallel_for(l2hl.ab2b.size(),f);
  return 0;
}
