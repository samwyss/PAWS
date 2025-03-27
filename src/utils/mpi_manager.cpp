#include "mpi_manager.h"

MPIManager::MPIManager(int &argc, char **argv) {
  MPI_Init(&argc, &argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_rank(comm, &rank);
  MPI_Comm_size(comm, &size);
}

MPIManager::~MPIManager() {
  MPI_Finalize();
}