#include <stdlib.h>
#include <strings.h>

#include "state.h"
#include "warn.h"

void
__shmem_environment_init()
{
}

#if 0

#define SHMEM_DEFAULT_BARRIER_ALGORITHM "linear"

void
__environment_init()
{
  char *ba = getenv("SHMEM_BARRIER_ALGORITHM");

  if (ba == (char *)NULL) {
    ba = SHMEM_DEFAULT_BARRIER_ALGORITHM;
  }

  if (strcasecmp(ba, "linear") == 0) {
    __shmem_dispatch[SHMEM_BARRIER_ALL_DISPATCH] = __shmem_barrier_all_linear;
  }
  else if (strcasecmp(ba, "dissemination") == 0) {
    __shmem_dispatch[SHMEM_BARRIER_ALL_DISPATCH] = __shmem_barrier_all_dissemination;
  else if (strcasecmp(ba, "tree") == 0) {
    __shmem_dispatch[SHMEM_BARRIER_ALL_DISPATCH] = __shmem_barrier_all_tree;
  else {
    __shmem_warn("NOTICE",
                 "unknown barrier algorithm \"%s\", using default (%s)\n",
                 ba,
                 SHMEM_DEFAULT_BARRIER_ALGORITHM
                );

    __shmem_dispatch[SHMEM_BARRIER_ALL_DISPATCH] = __shmem_barrier_all_linear;
  }
}

#endif
