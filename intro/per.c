#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int fd = open("/tmp/per-test.txt", O_WRONLY | O_CREAT | O_TRUNC | S_IRWXU);
  assert(fd > 1);

  int rc = write(fd, "hello world!", 13);
  assert(rc == 13);

  close(fd);

  return 0;
}
