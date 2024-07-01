#include <assert.h>
#include <pthread.h>
#include <stdlib.h>

#define Pthread_create(thread, attr, start_routine, arg)                       \
  assert(pthread_create(thread, attr, start_routine, arg) == 0);

#define Pthread_join(thread, value_ptr)                                        \
  assert(pthread_join(thread, value_ptr) == 0);

#define Malloc(s)                                                              \
  ({                                                                           \
    void *p = malloc(s);                                                       \
    assert(p != NULL);                                                         \
    p;                                                                         \
  })
