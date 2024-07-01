/// How to Use Inline Assembly Language in C Code?
///
/// https://gcc.gnu.org/onlinedocs/gcc/extensions-to-the-c-language-family/how-to-use-inline-assembly-language-in-c-code.html
/// https://stackoverflow.com/questions/71625166/trying-to-implement-a-spin-lock-via-lock-xchg-assembly

#include "common_threads.h"
#include <bits/pthreadtypes.h>
#include <stdio.h>
#include <string.h>

#define LOCK 1
#define UNLOCK 0

static volatile int counter = 0;
static int lock_t = 0;

int xchg(volatile int *addr, int newval) {
  int result;

  asm volatile("lock xchg %0, %1"
               : "+m"(addr), "=a"(result)
               : "m"(addr), "r"(newval)
               : "memory", "cc");

  return result;
}

void lock(int *lock) {
  while (!xchg(lock, LOCK))
    ;
}

void unlock(int *lock) { xchg(lock, UNLOCK); }

void *mythread(void *arg) {
  printf("%s: begin\n", (char *)arg);

  for (int i = 0; i < 1e7; i++) {
    lock(&lock_t);
    counter++;
    unlock(&lock_t);
  }

  printf("%s: end\n", (char *)arg);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "test") == 0) {
    lock(&lock_t);
    printf("lock: lock_t: %d\n", lock_t);

    unlock(&lock_t);
    printf("unlock: lock_t: %d\n", lock_t);

    return 0;
  }

  pthread_t p1, p2;

  printf("main: begin (counter = %d)\n", counter);

  Pthread_create(&p1, NULL, mythread, "A");
  Pthread_create(&p2, NULL, mythread, "B");

  Pthread_join(p1, NULL);
  Pthread_join(p2, NULL);

  printf("main: end (counter = %d)\n", counter);

  return 0;
}
