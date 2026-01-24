#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static unsigned int GENERATIONS = 0;

void build_tree(unsigned int n);
pid_t Fork();

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Not enough/too many arguments.\n");
    goto err;
  }

  GENERATIONS = atoi(argv[1]);
  if (!GENERATIONS) {
    printf("Parsing error: %s\n", argv[1]);
    goto err;
  }

  if (GENERATIONS > 10) {
    printf("<n> too large\n");
    goto err;
  }

  unsigned int depth = 0;
  for (;depth < GENERATIONS; ++depth) {
    printf("My generation is %u. (PID=%d, PPID=%d)\n", depth,
           getpid(), getppid());
    if (!Fork()) {
      continue;
    }
    if (!Fork()) {
      continue;
    }

    while (waitpid(-1, NULL, WNOHANG) > 0)
      ;
    break;
  }

  exit(EXIT_SUCCESS);
err:
  printf("\nUsage: tree_fork <n>\n"
         "<n> : the depth of the binary tree, between 0 and 10 (inclusive).\n");
  exit(EXIT_FAILURE);
}

pid_t Fork() {
  pid_t ret = fork();
  switch (ret) {
  case -1:
    printf("fork() error");
  default:
    return ret;
  }
}
