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

  LOs e2v({0, 1, 1, 2, 2, 3, 0, 3}, "e2v");
  LOs f2e({0, 1, 2, 3}, "f2e");
  auto f2v = transit(Adj(f2e), Adj(e2v), OMEGA_H_SIMPLEX, 2, 0);
  auto f = OMEGA_H_LAMBDA(LO i) {
    printf(" index %d, value %d \n", i, f2v.ab2b[i]);
  };
  parallel_for(f2v.ab2b.size(),f);

  return 0;
}
