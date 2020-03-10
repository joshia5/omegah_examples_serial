// This icode was written to try and step into
// the parallel vtk write API call for checking
// why we cannot visualize ghosted entities in paraview

#include <Omega_h_file.hpp>
#include <Omega_h_library.hpp>
#include <Omega_h_mesh.hpp>

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
  const auto rank = lib.world()->rank();
  const auto comm = lib.world();

  printf(" rank %d nverts %d nedges %d nelems %d \n", rank, mesh.nverts(), mesh.nedges(), mesh.nelems());
  //look at mesh::nghost_layers, set_parting(omega_h_ghosted)
  mesh.set_parting(OMEGA_H_GHOSTED, 1, 1);
  printf(" rank %d nverts %d nedges %d nelems %d \n", rank, mesh.nverts(), mesh.nedges(), mesh.nelems());
  vtk::write_parallel("/users/joshia5/new_mesh/ghosting_serial.vtk", &mesh, false);

  return 0;
}
