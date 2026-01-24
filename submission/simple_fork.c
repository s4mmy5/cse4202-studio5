#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
  printf("Parent: before fork\n");

  pid_t ret = fork();
  switch (ret) {
  case -1:
    printf("F*rking error\n");
    goto err;
    break;

  case 0:
    printf("Child: (PID=%d, PPID=%d)\n", getpid(), getppid());
    break;

  default:
    printf("Parent: after fork\n");
    pid_t child_pid = wait(0);

    if (child_pid == -1) {
      printf("Wait error: %d\n", child_pid);
      goto err;
    }

    printf("Parent: the child is dead (child PID=%d)\n", child_pid);
    break;
  }

  exit(EXIT_SUCCESS);
  err:
  exit(EXIT_FAILURE);
}
