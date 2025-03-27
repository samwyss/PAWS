#ifndef UTILS_MPIMANAGER_H
#define UTILS_MPIMANAGER_H

#include <mpi.h>

struct MPIManager {
  /*!
   * constructs MPIManager
   * @param argc command line argument count
   * @param argv command line argument vector
   */
  MPIManager(int &argc, char **argv);

  /*!
   * destructs MPIManager and finalizes MPI environment
   */
  ~MPIManager();

  /// MPI communicator
  MPI_Comm comm;

  /// rank within MPI communicator
  int rank = -1;

  /// size of MPI communicator
  int size = -1;
};

#endif //UTILS_MPIMANAGER_H