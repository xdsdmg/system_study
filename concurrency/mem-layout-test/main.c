#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#define Pthread_create(thread, attr, start_routine, arg)                       \
  assert(pthread_create(thread, attr, start_routine, arg) == 0);

#define Pthread_join(thread, value_ptr)                                        \
  assert(pthread_join(thread, value_ptr) == 0);

#define MINUTE 60

void *mythread(void *arg) {
  int local_var;

  // Print the variable's memory address
  printf("thread: %s, stack address: %p\n", (char *)arg, (void *)&local_var);

  while (1 == 1)
    sleep(5 * MINUTE);

  return NULL;
}

int main(int argc, char *argv[]) {
  pthread_t p1, p2;

  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");

  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);

  return 0;
}
