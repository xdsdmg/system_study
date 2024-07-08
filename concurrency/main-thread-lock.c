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

typedef volatile int vint;

static vint counter = 0;
static vint lock_t = 0;

int cmpxchgl(int expected, vint *status, int new_value) {
  asm volatile("lock cmpxchgl %2, %1"
               : "+a"(expected)
               : "m"(*status), "r"(new_value)
               : "memory", "cc");

  return expected;
}

int xchg(vint *addr, int newval) {
  int result;

  asm volatile("lock xchg %1, %0"
               : "=r"(result), "=m"(*addr)
               : "0"(newval), "m"(*addr)
               : "memory");

  return result;
}

void lock_cmpxchgl(vint *lock) {
  while (cmpxchgl(UNLOCK, lock, LOCK) != UNLOCK)
    ;
}

void unlock_cmpxchgl(vint *lock) {
  asm volatile("movl %1, %0" : "=m"(*lock) : "r"(UNLOCK) : "memory");
}

void lock_xchg(vint *lock) {
  while (xchg(lock, LOCK))
    ;
}

void unlock_xchg(vint *lock) { xchg(lock, UNLOCK); }

void *mythread(void *arg) {
  printf("%s: begin\n", (char *)arg);

  for (int i = 0; i < 1e7; i++) {
    lock_cmpxchgl(&lock_t);
    counter++;
    unlock_cmpxchgl(&lock_t);
  }

  printf("%s: end\n", (char *)arg);

  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc > 1 && strcmp(argv[1], "test_xchg") == 0) {
    lock_xchg(&lock_t);
    printf("lock: lock_t: %d\n", lock_t);

    unlock_xchg(&lock_t);
    printf("unlock: lock_t: %d\n", lock_t);

    return 0;
  }

  if (argc > 1 && strcmp(argv[1], "test_cmpxchgl") == 0) {
    lock_cmpxchgl(&lock_t);
    printf("lock: lock_t: %d\n", lock_t);

    unlock_cmpxchgl(&lock_t);
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
