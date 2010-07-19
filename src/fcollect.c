#include <sys/types.h>

#include "state.h"
#include "putget.h"
#include "warn.h"

#include "shmem.h"

#define SHMEM_FCOLLECT_TYPE(Size, Type)				\
  void shmem_fcollect##Size (void *target, const void *source, size_t nlong, \
			      int PE_start, int logPE_stride, int PE_size, \
			      long *pSync)				\
  {									\
    int i;								\
    const int step = 1 << logPE_stride;					\
    const int typed_len = nlong * sizeof(Type);				\
    void *walk = target;						\
    register int this_pe = PE_start;					\
    if (__state.mype == this_pe) {					\
      for (i = 0; i < PE_size; i += 1) {				\
	shmem_##Type##_get(walk, source, nlong, this_pe);		\
	walk += typed_len;						\
	this_pe += step;						\
      }									\
      shmem_barrier_all();						\
    }									\
    shmem_broadcast##Size (target, target, nlong * PE_size, 0, PE_start, logPE_stride, PE_size, pSync); \
  }

SHMEM_FCOLLECT_TYPE(32, int)
SHMEM_FCOLLECT_TYPE(64, long)
