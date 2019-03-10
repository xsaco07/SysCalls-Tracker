#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <stdlib.h>
#include <termios.h>
#include "SysCalls.h"

#define CHILD_DEFAULT_PID 0

int main(int argc, char *argv[]) {

  initialize_sys_calls_array();

  int proc_status;
  long sys_call_number;
  long sys_call_called = 0;
  struct user_regs_struct regs;

  pid_t child_pid = fork();

  if (child_pid < CHILD_DEFAULT_PID) { // Error in proccess
    perror("Error in fork()");
    exit(-1);
  }

  else if (child_pid == CHILD_DEFAULT_PID) { // Child proccess
    ptrace(PTRACE_TRACEME, CHILD_DEFAULT_PID, NULL, NULL);
    execvp(argv[1], argv+1);
  }
  else{ // Parent proccess
    while (1) {
      waitpid(-1, &proc_status, 0); // Wait for the kernel to tell us that the child process state has
                                    // changed or been interrupted

      if(WIFEXITED(proc_status)){ // Check wether the process has finished or exit
        break;
      }

      if (sys_call_called == 0) {
        sys_call_called = 1;
        ptrace(PTRACE_GETREGS, child_pid, NULL, &regs); // Get access to the registers where sys calls info is
        sys_call_number = regs.orig_rax;
        //printf("The system call number is: %ld\n", sys_call_number);
        sys_call_seen(sys_call_number);
      }
      else{
        sys_call_called = 0;
      }
      ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL);
    }
  }

  print_sys_calls_array();

  return 0;
}
