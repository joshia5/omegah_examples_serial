function(mpi_test TESTNAME PROCS EXE)
  add_test(
    NAME ${TESTNAME}
    COMMAND ${MPIRUN} ${MPIRUN_PROCFLAG} ${PROCS} ${EXE} ${ARGN}
  )
endfunction(mpi_test)

mpi_test(firstOrderAdj_2D 1  ./firstOrderAdjacency  ${CMAKE_SOURCE_DIR}/meshes/tri8.osh)
mpi_test(inversion_2D 1  ./inversion  ${CMAKE_SOURCE_DIR}/meshes/tri8.osh)
mpi_test(transition_2D 1  ./transition  ${CMAKE_SOURCE_DIR}/meshes/tri8.osh)
