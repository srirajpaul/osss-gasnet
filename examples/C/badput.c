/*
 * put from 0 (master) to PE 1, but with a non-symmetric variable
 */

#include <stdio.h>
#include <time.h>

#include <shmem.h>

int
main(int argc, char **argv)
{
  int dest;
  int src;
  int me, npes;

  shmem_init();

  me = shmem_my_pe();
  npes = shmem_num_pes();

  src = 42;

  shmem_barrier_all();

  if (me == 0) {
    shmem_int_put(&dest, &src, 1, 1);
  }

  shmem_barrier_all();

  return 0;
}
