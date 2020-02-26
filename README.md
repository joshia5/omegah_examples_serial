# omegah_examples
examples for getting started with omega_h


# build

The following instructions apply to the SCOREC RedHat 7 systems with NVIDIA
GPUs.  Specific instructions are given for Pascal GPUs (e.g., in the `blockade` and
`pachisi` systems).

## dependencies

First build the dependencies for execution with the Kokkos backend using CUDA.

Kokkos:
https://github.com/SCOREC/pumi-pic/wiki/Building-and-Running-on-SCOREC-RHEL7#kokkos

Omega_h:
https://github.com/SCOREC/pumi-pic/wiki/Building-and-Running-on-SCOREC-RHEL7#omega_h

Alternatively, for debugging purposes you can build Omega_h in serial without kokkos:

https://github.com/SCOREC/pumi-pic/wiki/Building-and-Running-on-SCOREC-RHEL7#building-omega_h-in-serial-for-debugging

Note, you'll still need to set `export oh=/path/to/omega_h/install` accordingly for the `omegah_examples` build.

## omegah_examples - cuda build

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
cmake ../omegah_examples -DCMAKE_CXX_COMPILER=mpicxx
make
```

Run `ctest` to run the examples:

```
ctest
```

## omegah_examples - serial build

Setup the environment.

```
module load gcc mpich cmake 
# use the environment variable set in the omega_h build
export CMAKE_PREFIX_PATH=$oh:$CMAKE_PREFIX_PATH
```

Clone the repo, run cmake, then build.

```
git clone git@github.com:SCOREC/omegah_examples.git
mkdir build-ohExamples-serial
cd !$
cmake ../omegah_examples -DCMAKE_CXX_COMPILER=g++
make
```

Run `ctest` to run the examples:

```
ctest
```

Note, any example using MPI will not compile. 


# add another example

Create a new source file from an existing one:

```
cd omegah_examples
cp firstOrderAdjacency.cpp foo.cpp
```

Add the new file to the build and test system cmake files:

`testing.cmake` - execution commands for examples, add `mpi_test(foo_2D 1 ./foo ${CMAKE_SOURCE_DIR}/meshes/tri8.osh)`
to start with, then modify as the new example is implemented

`CMakeLists.txt` - defines compile and link commands for examples; add `example(foo foo.cpp)`

Ensure that the new example compiles and runs:

```
# setup the environment as described above
cd build-ohExamples-pascal
make
ctest
```
