# omegah_examples
examples for getting started with omega_h


# build

The following instructions apply to the SCOREC RedHat 7 systems with NVIDIA
GPUs.  Specific instructions are given for Pascal GPUs (e.g., in the `blockade` and
`pachisi` systems).

## dependencies

First build the dependencies for execution with the Kokkos backend using CUDA.

Kokkos:
https://github.com/SCOREC/particle_structures/wiki/Building-and-Running-on-SCOREC-RHEL7#kokkos

Omega_h:
https://github.com/SCOREC/particle_structures/wiki/Building-and-Running-on-SCOREC-RHEL7#omega_h

## omegah_examples

Setup the environment.

```
module load cuda/10.1 gcc mpich cmake 
# use the environment variable set in the omega_h build
export CMAKE_PREFIX_PATH=$oh:$CMAKE_PREFIX_PATH
export MPICH_CXX=$kksrc/bin/nvcc_wrapper
```

Clone the repo, run cmake, then build.

```
git clone git@github.com:SCOREC/omegah_examples.git
mkdir build-ohExamples-pascal
cd !$
cmake ../kokkos -DCMAKE_CXX_COMPILER=mpicxx
make
```

Run `ctest` to run the examples:

```
ctest
```

# to add another example

Create a new source file from an existing one:

```
cd omegah_examples
cp firstOrderAdjacency.cpp foo.cpp
```

Add the new file to the build and test system cmake files:

`testing.cmake` - execution commands for examples, copy the lines for the
`firstOrderAdj_2D` to start with then modify as the new example is implemented
`CMakeLists.txt` - defines compile and link commands for examples

Ensure that the new example compiles and runs:

```
# setup the environment as described above
cd build-ohExamples-pascal
make
ctest
```
