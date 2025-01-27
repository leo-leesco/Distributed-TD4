#include <omp.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
  MPI_Init(NULL, NULL);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  printf("hello from thread %d/%d", rank, size);
  return EXIT_SUCCESS;
}
