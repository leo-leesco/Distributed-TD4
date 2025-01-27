/**
 * INF560 - TD4
 *
 * Part 2-a
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  int N;
  int seed;
  int i;
  int m = 0;
  double pi;
  double time_start, time_stop, duration;

  int N_threads = omp_get_num_threads();
  /* Check the number of command-line arguments */
  if (argc != 3) {
    fprintf(stderr, "Usage: %s N seed\n", argv[0]);
    return EXIT_FAILURE;
  }

  /* Grab the input parameters from command line */
  N = atoi(argv[1]);
  seed = atoi(argv[2]);

  /* Check input-parameter values */
  if (N <= 0) {
    fprintf(stderr, "Error: N should be positive\n");
    return EXIT_FAILURE;
  }

  printf("Running w/ N=%d, seed=%d\n", N, seed);

  /* Star timer */
  time_start = omp_get_wtime();

  double x, xtemp, y, ytemp;
#pragma omp parallel reduction(+ : m)
  {
    struct drand48_data randBuff;
    srand48_r(seed + omp_get_thread_num(),
              &randBuff); // Initialize with the same seed

#pragma omp for private(xtemp, ytemp, x, y)
    for (int i = 0; i < N; i++) {
      drand48_r(&randBuff, &xtemp);
      drand48_r(&randBuff, &ytemp);
      x = 1 - (2 * xtemp);
      y = 1 - (2 * ytemp);

      if ((x * x + y * y) < 1) {
#if DEBUG
#pragma omp critical
        {
          printf("x=%lf, y=%f is IN\n", x, y);
        }
#endif
        m++;
      } else {
#if DEBUG
#pragma omp critical
        {
          printf("x=%lf, y=%f is OUT\n", x, y);
        }
#endif
      }
    }
  }

  /* Stop timer */
  time_stop = omp_get_wtime();

#if DEBUG
  printf("m=%d\n", m);
#endif

  /* Compute value of PI */
  pi = (double)4 * m / N;

  printf("Result -> PI = %f\n", pi);

  /* Compute final duration (in seconds) */
  duration = time_stop - time_start;

  printf("Computed in %g s\n", duration);

  return EXIT_SUCCESS;
}
