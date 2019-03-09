#include <unistd.h>
#include <stdio.h>
#include <sys/ptrace.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

#define TRACER_OPTION_1 "-V"
#define TRACER_OPTION_2 "-v"
#define MAX_ARGS 10
#define TRUE 1
#define FALSE 0
#define CHILD_DEFAULT_PID 0

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

int main(int argc, char *argv[]){

	argument_count = argc;
	initialize_args_array();

	printf("\nThe first argument is: %s\n", argv[1]);

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

	PROG_ARGS[0] = PROG;
	take_prog_arguments_from_argv(argv);
	set_null_pointer_at_end(PROG_ARGS);

	printf("\nEl programa a ejecutar es %s\n", PROG);
	printf("\nLa lista de argumentos de %s son:\n", PROG);
	print_arguments(PROG_ARGS);
	printf("-------EJECUCION DEL OTRO PROGRAMA--------\n");

	execvp(PROG, PROG_ARGS);

	return 0;
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
