#include <Omega_h_file.hpp>
#include <Omega_h_library.hpp>
#include <Omega_h_mesh.hpp>

int main(int argc, char** argv) {
  auto lib = Omega_h::Library(&argc, &argv);
  if(argc!=2) {
    fprintf(stderr, "Usage: %s <input mesh>\n", argv[0]);
    return 0;
  }
  const auto rank = lib.world()->rank();
  const auto inmesh = argv[1];
  Omega_h::Mesh mesh(&lib);
  Omega_h::binary::read(inmesh, lib.world(), &mesh);
  const auto dim = mesh.dim();
  if(!rank) {
    fprintf(stderr, "mesh <v e f r> %d %d %d %d\n",
        mesh.nglobal_ents(0),
        mesh.nglobal_ents(1),
        mesh.nglobal_ents(2),
        dim == 3 ? mesh.nglobal_ents(3) : 0);
  }

  //-- upward adjacencies --//
  //get array of vertices to edges

  //get array of edges to faces

  //get array of faces to regions (if 3D mesh)

  //-- downward adjacencies --//
  //get array of regions to faces (if 3D mesh)

  //get array of faces to edges

  //get array of edges to vertices

  return 0;
}
