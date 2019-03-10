#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include "SysCalls.h"

#define TRACER_OPTION_1 "-V"
#define TRACER_OPTION_2 "-v"
#define MAX_ARGS 10
#define TRUE 1
#define FALSE 0
#define CHILD_DEFAULT_PID 0
#define PROG_NAME_POSITION 0

char* PROG;
char* PROG_ARGS[MAX_ARGS];
int argument_count = 0;
int TRACER_FLAG_1 = FALSE;
int TRACER_FLAG_2 = FALSE;
int NO_TRACER_FLAG = FALSE;

void initialize_args_array();
void copy_args_starting_from(char* array1[], char* array2[], int init_pos);
void set_null_pointer_at_end(char* array[]);
void print_arguments(char* array[]);
_Bool prog_at_position_has_arguments(int position);
_Bool V_flag_found();
void take_prog_arguments_from_argv(char* argv[]);
void manage_arguments(char* argv[]);
void manage_V_argument(char* argv[]);

int main(int argc, char *argv[]){

	argument_count = argc;

	initialize_args_array();

	manage_arguments(argv);

	initialize_sys_calls_array();

  int proc_status;
  long sys_call_number;
  long sys_call_called = FALSE;
  struct user_regs_struct regs;

  pid_t child_pid = fork();

  if (child_pid < CHILD_DEFAULT_PID) { // Error in proccess
    perror("Error in fork()");
    exit(-1);
  }

  else if (child_pid == CHILD_DEFAULT_PID) { // This is the child proccess
		printf("\nThe program %s will be executed\n", PROG);
		printf("\nThe arguments of %s are:\n", PROG);
		print_arguments(PROG_ARGS);
		printf("-------PROG EXECUTION--------\n\n");
    ptrace(PTRACE_TRACEME, CHILD_DEFAULT_PID, NULL, NULL);
    execvp(PROG, PROG_ARGS);
  }
  else{ // This is the parent proccess
    while (TRUE) {
      waitpid(-1, &proc_status, 0); // Wait for the kernel to tell us that the child process state has
                                    // changed or been interrupted

      if(WIFEXITED(proc_status)){ // Check wether the process has finished or exit
        break;
      }

      if (sys_call_called == FALSE) {

        ptrace(PTRACE_GETREGS, child_pid, NULL, &regs); // Get access to the registers where sys calls info is

				sys_call_number = regs.orig_rax;

				if (TRACER_FLAG_1) {
					print_sys_call_info(sys_call_number);
					getchar(); // Wait for the user to press a key
				}
				else if (TRACER_FLAG_2) {
					print_sys_call_info(sys_call_number);
				}

        sys_call_seen(sys_call_number);

				sys_call_called = TRUE;

      }
      else{
        sys_call_called = FALSE;
      }
      ptrace(PTRACE_SYSCALL, child_pid, NULL, NULL); // Restart the the process with pid child_pid
    }

		printf("\n-------FINAL SYS_CALLS TABLE--------\n");
	  print_sys_calls_array();
  }

	return 0;
}

void manage_arguments(char* argv[]){
	printf("\nThe first argument is: %s\n", argv[1]);
	manage_V_argument(argv);
	PROG_ARGS[PROG_NAME_POSITION] = PROG;
	take_prog_arguments_from_argv(argv);
	set_null_pointer_at_end(PROG_ARGS);
}

void take_prog_arguments_from_argv(char* argv[]){
	if (V_flag_found()) {
		if (prog_at_position_has_arguments(2)) {
			copy_args_starting_from(PROG_ARGS, argv, 3);
		}
	}
	else{
		if (prog_at_position_has_arguments(1)) {
			copy_args_starting_from(PROG_ARGS, argv, 2);
		}
	}
}

void manage_V_argument(char* argv[]){
	if (!strcmp(argv[1], TRACER_OPTION_1)) { // -V flag found
		printf("\nHas -V\n");
		TRACER_FLAG_1 = TRUE;
		PROG = argv[2]; // Save PROG name
	}
	else if (!strcmp(argv[1], TRACER_OPTION_2)) { // -v flag found
		printf("\nHas -v\n");
		TRACER_FLAG_2 = TRUE;
		PROG = argv[2]; // Save PROG name
	}
	else{
		printf("\nHas no -V or -v flag\n");
		NO_TRACER_FLAG = TRUE;
		PROG = argv[1]; // Save PROG name
	}
}

_Bool V_flag_found(){
	return TRACER_FLAG_1 || TRACER_FLAG_2;
}

void initialize_args_array(){
	for(int i = 1; i < MAX_ARGS; i++){
		PROG_ARGS[i] = "";
	}
}

_Bool prog_at_position_has_arguments(int position){
	return argument_count > (position+1);
}

// Take elements from array2 starting from init_pos and copy them to array1
void copy_args_starting_from(char* array1[], char* array2[], int init_pos){
	for(int index = 1; init_pos < argument_count; index++){
		array1[index] = array2[init_pos];
		init_pos++;
	}
}

void set_null_pointer_at_end(char* array[]){
	int index = 0;
	while (array[index] != "") {
		index++;
	}
	array[index] = NULL;
}

void print_arguments(char* array[]){
	for(int index = 0; array[index] != ""; index++){
		printf("\n->%s\n", array[index]);
	}
	printf("\n");
}
