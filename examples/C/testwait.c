/*
 * PE 1 waits for PE 0 to send something other than 9.
 * Send 4 9s to test wait condition, then some random values until != 9.
 */

#include <stdio.h>
#include <shmem.h>

int
main(void)
{
  int me, npes;
  long *dest;

  {
    time_t now;
    time(&now);
    srand( now + getpid() );
  }

  shmem_init();
  me = shmem_my_pe();
  npes = shmem_num_pes();

  dest = (long *) shmalloc( sizeof(*dest) );
  shmem_barrier_all();

  *dest = 9L;

  shmem_barrier_all();

  if (me == 0) {
    int i;
    for (i = 0; i < 4; i += 1) {
      long src = 9L;
      shmem_long_put(dest, &src, 1, 1);
      fprintf(stderr, "PE %d put %d\n", me, src);
    }
    fprintf(stderr, "----------------------------\n");
    for (i = 0; i < 1000; i += 1) {
      long src = rand() % 10;
      shmem_long_put(dest, &src, 1, 1);
      fprintf(stderr, "PE %d put %d\n", me, src);
      if (src != 9L)
        break;
    }
  }

  shmem_barrier_all();

  if (me == 1) {
    shmem_long_wait(dest, 9L);
  shmem_barrier_all();
    fprintf(stderr, "PE %d finished wait, got %d\n", me, *dest);
  }

  shmem_barrier_all();

  return 0;
}
