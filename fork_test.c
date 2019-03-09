#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

#define CHILD_DEFAULT_PID 0

int main(int argc, char const *argv[]) {

  pid_t child_pid = fork();

  if (child_pid < 0) { // Error in proccess
    perror("Error in fork()");
    exit(-1);
  }

  else if (child_pid > 0) { // Parent proccess
    wait()
  }
  else{ // Child proccess

  }

  return 0;
}
